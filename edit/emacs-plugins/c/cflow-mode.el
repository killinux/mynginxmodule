;;; cflow.el --- major mode for viewing cflow output files.

;; Authors: 1994, 1995, 2005, 2007 Sergey Poznyakoff; 2010 John Sturdy
;; Version: 0.3
;; Keywords: cflow
;; $Id$

;; This file is part of GNU cflow
;; Copyright (C) 1994, 1995, 2005, 2007, 2010 Sergey Poznyakoff and 2010 John Sturdy
 
;; GNU cflow is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3 of the License, or
;; (at your option) any later version.
 
;; GNU cflow is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GNU cflow; if not, write to the Free Software Foundation,
;; Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

;; Installation:
;; You may wish to use precompiled version of the module. To create it
;; run:
;;    emacs -batch -f batch-byte-compile cflow-mode.el
;; Install the file cflow-mode.elc (and, optionally, cflow-mode.el) to
;; any directory in your Emacs load-path.

;; Customization:
;;  To your .emacs or site-start.el add:
;;  (autoload 'cflow-mode "cflow-mode")
;;  (setq auto-mode-alist (append auto-mode-alist
;;                                '(("\\.cflow$" . cflow-mode))))

;; The variable `cflow-display-functions' controls whether the
;; function on the current line is displayed in another window.  If it
;; is set to the symbol `narrowed', which is the default, the buffer
;; in that window is narrowed to display only that function.

;; The variable `cflow-next-previous-functions-only' being non-nil
;; makes the mode's motion commands move only onto functions defined
;; in the files mentioned in the cflow file.

;; The variable `cflow-backtrack-invisible' controls whether the mode
;; offers to go back to a section that has been folded away using
;; `outline-minor-mode', on reaching the end of a subtree.
;; Furthermore, if it is set to the symbol `no-ask', it does so
;; without asking.

(eval-when-compile
  ;; We use functions from these modules
  (mapcar 'require '(font-lock)))

(defvar cflow-display-functions 'narrowed
  "Whether to display each function that we move onto.
If it is the symbol `narrowed', narrow to just that function.")

(defvar cflow-next-previous-functions-only t
  "Whether the `next' and `previous' movements should go to our next function.")

(defvar cflow-backtrack-invisible 'no-ask
  "*Whether to go back to folded sections on reaching the end of a subtree.
If it is the symbol `no-ask', do this without asking.")

(defvar cflow-function-regexp "\\([^ \t:]+\\):\\([0-9]+\\)"
  "Pattern for a default function in cflow output.")

(defvar cflow-new-function-regexp (concat cflow-function-regexp ">\\(?: (R)\\)?:?$")
  "Pattern for the first occurrence of a default function in cflow output.")

(defvar cflow-mode-syntax-table nil
  "Syntax table used in cflow-mode buffers.")

(unless cflow-mode-syntax-table
  (setq cflow-mode-syntax-table (make-syntax-table))
  (modify-syntax-entry ?\# "<" cflow-mode-syntax-table)
  (modify-syntax-entry ?\n ">" cflow-mode-syntax-table))

(defvar cflow-mode-map (make-sparse-keymap)
  "Keymap used in Cflow mode.")

(define-key cflow-mode-map "s" 'cflow-find-function)
(define-key cflow-mode-map "o" 'cflow-find-function-other-window)
(define-key cflow-mode-map "d" 'cflow-display-function-other-window)
(define-key cflow-mode-map "1" 'delete-other-windows)
(define-key cflow-mode-map "b" 'cflow-backward-same-level)
(define-key cflow-mode-map "f" 'cflow-forward-same-level)
(define-key cflow-mode-map "u" 'cflow-up-level)
(define-key cflow-mode-map " " 'cflow-scroll-other-window)
(define-key cflow-mode-map "\d" 'cflow-scroll-other-window-down)
(define-key cflow-mode-map "r" 'cflow-recursion-root)
(define-key cflow-mode-map "R" 'cflow-recursion-next)
(define-key cflow-mode-map "x" 'cflow-goto-expand)
(define-key cflow-mode-map "?" 'cflow-get-stack)
(define-key cflow-mode-map "E" 'cflow-edit-out-full)
(define-key cflow-mode-map "\t" 'cflow-hide-or-show-subtree)
(define-key cflow-mode-map "n" 'cflow-next-line)
(define-key cflow-mode-map "p" 'cflow-previous-line)

(define-key cflow-mode-map [menu-bar] (make-sparse-keymap))

(define-key cflow-mode-map [menu-bar cflow]
  (cons "Cflow" (make-sparse-keymap "Cflow")))

(define-key cflow-mode-map [menu-bar cflow cflow-recursion-next]
  '("Recursion next" . cflow-recursion-next))
(define-key cflow-mode-map [menu-bar cflow cflow-recursion-root]
  '("Recursion root" . cflow-recursion-root))
(define-key cflow-mode-map [menu-bar cflow cflow-goto-expand]
  '("Find expansion" . cflow-goto-expand))
(define-key cflow-mode-map [menu-bar cflow cflow-find-function]
  '("Find function" . cflow-find-function))

;; Toggle visibility of subtree
(defun cflow-hide-or-show-subtree ()
  "Toggle visibility of the subtree starting on the current line.
Uses function `outline-minor-mode'."
  (interactive)
  (unless outline-minor-mode
    (outline-minor-mode 1))
  (if (get-char-property (line-end-position) 'invisible)
      (show-subtree)
    (hide-subtree)))

(defun cflow-backward-to-function ()
  "Move backward to a function line, if not already on one."
  (when cflow-next-previous-functions-only
    (if (re-search-backward cflow-new-function-regexp (point-min) t)
	(back-to-indentation)
      (error "No previous function"))))

(defun cflow-previous-line ()
  "Move to the next line.
If `cflow-display-functions' is non-nil, display the function on this line,
if there is one."
  (interactive)
  (cflow-backward-to-function)
  (when cflow-display-functions
    (cflow-display-function-other-window t)))

(defun cflow-level ()
  "Return the indentation level."
  (save-excursion
    (beginning-of-line)
    (if (re-search-forward outline-regexp (point-max) t)
	(current-column)
      0)))

(defun cflow-forward-to-function ()
  "Move forward to the next function line, if not already on one."
  (when cflow-next-previous-functions-only
    (if (re-search-forward cflow-new-function-regexp (point-max) t)
	(back-to-indentation)
      (error "No next function"))))

(defun cflow-next-line ()
  "Move to the next line.
If `cflow-display-functions' is non-nil, display the function on this line,
if there is one."
  (interactive)
  (let ((old-level (cflow-level)))
    (next-line 1)
    (cflow-forward-to-function)
    (when (< (cflow-level) old-level)
      (let ((previous-invisibility-change
	     (previous-single-char-property-change (point) 'invisible)))
	(when (and previous-invisibility-change
		   (>= (save-excursion
			 (goto-char previous-invisibility-change)
			 (cflow-level))
		       old-level)
		   (or (eq cflow-backtrack-invisible 'no-ask)
		       (and cflow-backtrack-invisible
			    (y-or-n-p "Backtrack to folded section? "))))
	  (goto-char (previous-single-char-property-change previous-invisibility-change 'invisible))
	  (back-to-indentation)
	  (save-excursion
	    (show-subtree))
	  (message "Backtracked to previously folded subtree"))))
    (when cflow-display-functions
      (cflow-display-function-other-window t))))

(defun cflow-backward-same-level ()
  "Move to the previous line at the same level.
If `cflow-display-functions' is non-nil, display the function on this line,
if there is one."
  (interactive)
  (outline-backward-same-level 1)
  (back-to-indentation)
  (cflow-backward-to-function)
  (when cflow-display-functions
    (cflow-display-function-other-window t)))

(defun cflow-forward-same-level ()
  "Move to the next line at the same level.
If `cflow-display-functions' is non-nil, display the function on this line,
if there is one."
  (interactive)
  (outline-forward-same-level 1)
  (back-to-indentation)
  (cflow-forward-to-function)
  (when cflow-display-functions
    (cflow-display-function-other-window t)))

(defun cflow-up-level ()
  "Move to the previous line at the next level up.
If `cflow-display-functions' is non-nil, display the function on this line,
if there is one."
  (interactive)
  (outline-up-heading 1)
  (back-to-indentation)
  (when cflow-display-functions
    (cflow-display-function-other-window t)))

(defun cflow-scroll-other-window ()
  "Scroll the other window.
If it is at the end of its buffer, move to the next listed function."
  (interactive)
  (let ((source-window (condition-case evar
			   (other-window-for-scrolling)
			 (error nil))))
    (if source-window
	(let ((source-position (window-start source-window)))
	  (scroll-other-window)
	  (when (= source-position (window-start source-window))
	    (cflow-next-line)))
      (when cflow-display-functions
	(cflow-display-function-other-window t)))))

(defun cflow-scroll-other-window-down ()
  "Scroll the other window down.
If it is at the start of its buffer, move to the previous listed function."
  (interactive)
  (let ((source-window (condition-case evar
			   (other-window-for-scrolling)
			 (error nil))))
    (if source-window
	(let ((source-position (window-start source-window)))
	  (scroll-other-window-down nil)
	  (when (= source-position (window-start source-window))
	    (cflow-previous-line)))
      (when cflow-display-functions
	(cflow-display-function-other-window t)))))

(defun cflow-get-stack (&optional display)
  "Return the statically calculated stack.
Called interactively, or with arg DISPLAY, display it in the message buffer."
  (interactive (list t))
  (let ((stack nil))
    (save-excursion
      (while
	  (condition-case evar
	      (progn
		(outline-up-heading 1)
		(back-to-indentation)
		(push (symbol-at-point) stack)
		t)
	    (error nil))))
    (when display
      (message "Calls: %s" (mapconcat 'symbol-name stack " ==> ")))
    stack))

;; Find the function under cursor.
;; Switch to the proper buffer and go to the function header
(defun cflow-find-function ()
  "Find the function on the current line."
  (interactive)
  (let ((lst (cflow-find-default-function)))
    (cond
     (lst
      (switch-to-buffer (find-file-noselect (car lst)))
      (goto-line (car (cdr lst))))
     (t
      (error "No source/line information for this function")))))

(defun cflow-find-function-other-window ()
  "Find the function on the current line, in the other window."
  (interactive)
  (let ((lst (cflow-find-default-function)))
    (cond
     (lst
      (switch-to-buffer-other-window (find-file-noselect (car lst)))
      (goto-line (car (cdr lst))))
     (t
      (error "No source/line information for this function")))))

(defun cflow-display-function-other-window (&optional no-error)
  "Display the function on the current line, in the other window.
Optional argument NO-ERROR means not to complain if the line has no function."
  (interactive)
  (let ((lst (cflow-find-default-function)))
    (cond
     (lst
      (let* ((cflow-window (selected-window))
	     (pop-up-windows (eq cflow-window (next-window))))
	(pop-to-buffer (find-file-noselect (car lst)) t)
	(widen)
	(goto-line (car (cdr lst)))
	(when (eq cflow-display-functions 'narrowed)
	  (narrow-to-defun))
	(select-window cflow-window)))
     (t
      (unless no-error
	(error "No source/line information for this function"))))))

(defun cflow-find-default-function ()
  "Parse a cflow listing line.
Return (list SOURCE-NAME LINE-NUMBER)"
  (save-excursion
    (beginning-of-line)
    (cond
     ((re-search-forward cflow-function-regexp
			 (save-excursion (end-of-line) (point))
			 t)
      (list
       (buffer-substring (match-beginning 1) (match-end 1))
       (string-to-number
	(buffer-substring (match-beginning 2) (match-end 2)))))
     (t
      nil))))

;; If the cursor stays on a recursive call, then go to the root of
;; this call
(defun cflow-recursion-root ()
  (interactive)
  (let ((num (cond
	      ((save-excursion
		 (beginning-of-line)
		 (re-search-forward "(recursive: see \\([0-9]+\\))"
				    (save-excursion (end-of-line) (point))
				    t))
	       (string-to-number
		(buffer-substring (match-beginning 1) (match-end 1))))
	      (t
	       0))))
    (cond
     ((> num 0)
      (push-mark)
      (goto-line num))
     (t
      (error "Not a recursive call")))))

(defun cflow-recursion-next ()
  "Go to next recursive call"
  (interactive)
  (save-excursion
    (beginning-of-line)
    (cond
     ((re-search-forward "(R)"
			 (save-excursion (end-of-line) (point)) t)
      (setq cflow-recursion-root-line (count-lines 1 (point))))))
  (cond
   ((null cflow-recursion-root-line)
    (error "No recursive functions"))
   (t
    (let ((pos (save-excursion
		 (next-line 1)
		 (re-search-forward
		  (concat "(recursive: see "
			  (number-to-string cflow-recursion-root-line)
			  ")")
		  (point-max)
		  t))))
      (cond
       ((null pos)
	(goto-line cflow-recursion-root-line)
	(error "no more calls."))
       (t
	(push-mark)
	(goto-char pos)
	(beginning-of-line)))))))

(defun cflow-goto-expand ()
  (interactive)
  (let ((num (cond
	      ((save-excursion
		 (beginning-of-line)
		 (re-search-forward "\\[see \\([0-9]+\\)\\]"
				    (save-excursion (end-of-line) (point))
				    t))
	       (string-to-number
		(buffer-substring (match-beginning 1) (match-end 1))))
	      (t
	       0))))
    (cond
     ((> num 0)
      (push-mark)
      (goto-line num))
     (t
      (error "not expandable")))))

(defvar cflow-read-only)

(defun cflow-edit-out-full ()
  "Get out of Cflow mode, leaving Cflow file buffer in fundamental mode."
  (interactive)
  (if (yes-or-no-p "Should I let you edit the whole Cflow file? ")
      (progn
	(setq buffer-read-only cflow-read-only)
	(fundamental-mode)
	(message "Type 'M-x cflow-mode RET' once done"))))


;; Font-lock stuff
(defconst cflow-font-lock-keywords
  (eval-when-compile
    (list
     (cons "^\\s *[0-9]+" font-lock-constant-face)
     (list "\\(\\S +\\)()\\s +\\(<[^>]*>\\)"
	   '(1 font-lock-function-name-face)
	   '(2 font-lock-type-face))
     (list "\\(\\S +\\)\\s +\\(<[^>]*>\\)"
	   '(1 font-lock-variable-name-face)
	   '(2 font-lock-type-face))
     (cons "\\S +()$" font-lock-builtin-face)
     (cons "(R):?$" font-lock-comment-face)
     (cons "(recursive: see [0-9]+)" font-lock-comment-face)
     (cons "^[ \\t+-|\\]+" font-lock-keyword-face))))

;;;###autoload
(defun cflow-mode ()
  "Major mode for viewing cflow output files.
\\<cflow-mode-map>
`\\[cflow-next-line]' and `\\[cflow-previous-line]' move to next and previous functions.

`\\[cflow-forward-same-level]' and `\\[cflow-backward-same-level]' move forward and backward at the same level,
and `\\[cflow-up-level]' goes up a level; `\\[cflow-hide-or-show-subtree]' toggles hiding the subtree at point.

If the variable `cflow-display-functions' is non-nil, the current function is
displayed in another window after each movement, and `\\[cflow-scroll-other-window]' and `\\[cflow-scroll-other-window-down]' scroll
the other window (and on to the next function on reaching the end of it),
and `\\[delete-other-windows]' closes the other window.

If `cflow-display-functions' is set to the symbol 'narrowed, the
window is narrowed to just that function.

Setting the variable `cflow-backtrack-invisible' non-nil will ask
to reveal, and continue from, a previous hidden section within a
level, on reaching the end of the level.  If set to the symbol
'no-ask, it will do it without asking.

`\\[cflow-get-stack]' shows the call stack needed to get to the current line.

Key bindings are:
\\{cflow-mode-map}"
  (interactive)
  (kill-all-local-variables)
  (use-local-map cflow-mode-map)
  (setq major-mode 'cflow-mode
	mode-name "Cflow")
  (make-variable-buffer-local 'cflow-recursion-root-line)

  (set (make-local-variable 'cflow-read-only) buffer-read-only)
  (setq buffer-read-only t)

  (set-default 'cflow-recursion-root-line nil)

  (set-syntax-table cflow-mode-syntax-table)

  (make-local-variable 'font-lock-defaults)
  (setq font-lock-defaults
	'((cflow-font-lock-keywords) nil t
	  (("+-*/.<>=!?$%_&~^:" . "w"))
	  beginning-of-line)
	outline-regexp " +")
  (save-excursion
    ;; Because " *" doesn't work as `outline-regexp', we set it to "
    ;; +", and so to make the top of the tree be a proper node, we'll
    ;; force it to match `outline-regexp'
    (goto-char (point-min))
    (unless (looking-at " ")
      (let ((buffer-read-only nil))
	(insert " ")
	(put-text-property (point-min) (1+ (point-min)) 'invisible t)))))

(provide 'cflow-mode)
;;; cflow-mode ends
