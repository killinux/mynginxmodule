(global-set-key (kbd "<f11>") 'rename-buffer)
(when (fboundp 'winner-mode)
  (winner-mode)
  (windmove-default-keybindings))

(define-prefix-command 'ctl-z-map)
(global-set-key (kbd "C-z") 'ctl-z-map)
(global-set-key (kbd "C-z C-z") 'linum-mode)
(global-set-key (kbd "C-z C-f") 'goto-line)

;括号匹配
(global-set-key "%" 'match-paren)   
(defun match-paren (arg)   
  "Go to the matching paren if on a paren; otherwise insert %."   
  (interactive "p")   
  (cond ((looking-at "\\s\(") (forward-list 1) (backward-char 1))   
        ((looking-at "\\s\)") (forward-char 1) (backward-list 1))   
        (t (self-insert-command (or arg 1)))))  

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

(setq tags-file-name "/data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6/TAGS")

(setq default-directory "/data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6")
(setq x-select-enable-clipboard t)
(setq backup-directory-alist '(("." . "/data/haoning/mygit/mynginxmodule/edit/configbackup")))

(setq tab-width 4)
(setq default-tab-width 4)
(setq indent-tabs-mode t)(setq c-basic-offset 4)
;; C language setting
(add-hook 'c-mode-hook 
         '(lambda ()
             (c-set-style "K&R")
             (setq tab-width 4)
             (setq indent-tabs-mode t)
             (setq c-basic-offset 4)))
;; C++ language setting
(add-hook 'c++-mode-hook
          '(lambda ()
             (c-set-style "K&R")
             ;;(c-toggle-auto-state)
             (setq tab-width 4)
             (setq indent-tabs-mode t)
             (setq c-basic-offset 4)))

(global-hl-line-mode 1)
