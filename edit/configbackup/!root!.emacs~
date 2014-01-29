
(put 'upcase-region 'disabled nil)
(set-language-environment 'utf-8)
(set-keyboard-coding-system 'utf-8)
(set-clipboard-coding-system 'euc-cn)
(set-terminal-coding-system 'utf-8)
(set-buffer-file-coding-system 'euc-cn)
(set-selection-coding-system 'euc-cn)
(modify-coding-system-alist 'process "*" 'utf-8)
(setq default-process-coding-system '(euc-cn . euc-cn))
(setq-default pathname-coding-system 'utf-8)

(add-to-list 'load-path "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/auto-complete")  
(require 'auto-complete-config)  
(add-to-list 'ac-dictionary-directories "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/auto-complete/ac-dict")  
(ac-config-default)
(add-to-list 'load-path "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/c")  
(require 'gccsense)  
(global-set-key "\257" (quote ac-complete-gccsense))

(global-set-key (kbd "<f11>") 'rename-buffer)

(when (fboundp 'winner-mode) 
  (winner-mode) 
  (windmove-default-keybindings)) 

(require 'xcscope)
(setq cscope-do-not-update-database t)

(define-prefix-command 'ctl-z-map)
(global-set-key (kbd "C-z") 'ctl-z-map)
(global-set-key (kbd "C-z C-z") 'linum-mode)
(global-set-key (kbd "C-z C-f") 'goto-line)
;(load-file "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/c/graphviz-dot-mode.el")
(setq tags-file-name "/data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6/TAGS")

;(global-hl-line-mode 1)
(require 'unicad)
(load-file "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/c/cedet-1.0.1/common/cedet.el")
(require 'cedet)
(add-to-list 'load-path "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/c/ecb-2.40")
(require 'ecb) 
(setq ecb-tip-of-the-day nil)
(global-set-key (kbd "C-z h") 'windmove-left)
(global-set-key (kbd "C-z l") 'windmove-right)
(global-set-key (kbd "C-z p") 'windmove-up)
(global-set-key (kbd "C-z n") 'windmove-down)

;;;自动启动ecb
;; (setq ecb-auto-activate t)
;;;一键开关
(defun my-ecb-active-or-deactive ()
  (interactive)
  (if ecb-minor-mode
      (ecb-deactivate)
    (ecb-activate)))

(global-set-key (kbd "C-z q") 'my-ecb-active-or-deactive)
(global-set-key (kbd "C-z C-s") 'ecb-show-ecb-windows)
(global-set-key (kbd "C-z C-h") 'ecb-hide-ecb-windows)

(global-set-key (kbd "C-z d") 'ecb-maximize-window-directories)
(global-set-key (kbd "C-z s") 'ecb-maximize-window-sources)
(global-set-key (kbd "C-z m") 'ecb-maximize-window-methods)
(global-set-key (kbd "C-z h") 'ecb-maximize-window-history)
(global-set-key (kbd "C-z r") 'ecb-restore-default-window-sizes)
(global-set-key (kbd "C-z C-l") 'windmove-left)
(global-set-key (kbd "C-z C-r") 'windmove-right)
(global-set-key (kbd "C-z C-u") 'windmove-up)
(global-set-key (kbd "C-z C-d") 'windmove-down)

(load-file "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/c/session/lisp/session.el")
(require 'session)
(add-hook 'after-init-hook 'session-initialize)
;(require 'doxymacs) 

(global-set-key [(f5)] 'speedbar)

(require 'ibuffer)
(global-set-key (kbd "C-x C-b") 'ibuffer)

(setq default-directory "/data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6")   
(setq x-select-enable-clipboard t)   
(setq backup-directory-alist '(("." . "/data/haoning/mygit/mynginxmodule/edit/configbackup")))

(require 'ido)
(ido-mode t)

(load-file "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/c/tabbar.el")
(require 'tabbar)
(tabbar-mode 1)
(global-set-key [(meta j)] 'tabbar-backward)  
(global-set-key [(meta k)] 'tabbar-forward) 

;(require 'rect-mark)

(global-set-key [(meta ?/)] 'hippie-expand)
(setq hippie-expand-try-functions-list 
      '(try-expand-dabbrev
	try-expand-dabbrev-visible
	try-expand-dabbrev-all-buffers
	try-expand-dabbrev-from-kill
	try-complete-file-name-partially
	try-complete-file-name
	try-expand-all-abbrevs
	try-expand-list
	try-expand-line
	try-complete-lisp-symbol-partially
	try-complete-lisp-symbol))

;括号匹配
(global-set-key "%" 'match-paren)
(defun match-paren (arg)
  "Go to the matching paren if on a paren; otherwise insert %."
  (interactive "p")
  (cond ((looking-at "\\s\(") (forward-list 1) (backward-char 1))
	((looking-at "\\s\)") (forward-char 1) (backward-list 1))
	(t (self-insert-command (or arg 1)))))

(global-set-key (kbd "C-z t") 'say-hello) 
(defun say-hello()(interactive)(print system-type))
;(defun say-hello()(interactive)(print "hello haoning"))

(require 'tramp)
(cond
 ((eq system-type 'windows-nt)
  (setq tramp-default-method "plink"
        tramp-password-end-of-line "\r\n"))
 ((eq system-type 'gnu/linux)
  (setq tramp-default-method "ssh")))
(setq tramp-default-user "root"
         tramp-default-host "106.187.88.34")
(setq password-cache-expiry 36000)


(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(ecb-layout-window-sizes nil)
 '(ecb-options-version "2.40")
 '(ecb-source-path (quote (("/data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6/" "/hn"))))
 '(session-use-package t nil (session)))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 )

(require 'cflow-mode)
(defvar cmd nil nil)
(defvar cflow-buf nil nil)
(defvar cflow-buf-name nil nil)
 
(defun yyc/cflow-function (function-name)
  "Get call graph of inputed function. "
  ;(interactive "sFunction name:\n")
  (interactive (list (car (senator-jump-interactive "Function name: "
                                                    nil nil nil))))
  (setq cmd (format "cflow  -b --main=%s %s" function-name buffer-file-name))
  (setq cflow-buf-name (format "**cflow-%s:%s**"
                               (file-name-nondirectory buffer-file-name)
                               function-name))
  (setq cflow-buf (get-buffer-create cflow-buf-name))
  (set-buffer cflow-buf)
  (setq buffer-read-only nil)
  (erase-buffer)
  (insert (shell-command-to-string cmd))
  (pop-to-buffer cflow-buf)
  (goto-char (point-min))
  (cflow-mode)
  )
(print "hello emacs end")