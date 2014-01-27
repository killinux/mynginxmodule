
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
(global-set-key (kbd "C-z C-a") 'goto-line)
;(load-file "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/c/graphviz-dot-mode.el")
(setq tags-file-name "/data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6/TAGS")

;(global-hl-line-mode 1)
(require 'unicad)
(load-file "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/c/cedet-1.1/common/cedet.el")
(require 'cedet)
;(require 'ecb) 
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

