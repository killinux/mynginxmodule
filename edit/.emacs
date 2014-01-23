
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

(global-set-key (kbd "C-c z") 'shell)
(global-set-key (kbd "<f10>") 'rename-buffer)

(when (fboundp 'winner-mode) 
  (winner-mode) 
  (windmove-default-keybindings)) 
;然后就可以使用 Ctrl-c ← （对，就是向左的箭头键）组合键，退回你的上一个窗口设置。

(add-to-list 'load-path "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/weibo.emacs-master")
(require 'weibo)

(add-to-list 'load-path' "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/cscope-plugin")
(require 'xcscope)
;只在打开c/c++文件的时候才加载xcscope，可以加入
(add-hook 'c-mode-common-hook '(lambda() (require 'xcscope)))
(define-key global-map [(control f3)]  'cscope-set-initial-directory)
(define-key global-map [(control f4)]  'cscope-unset-initial-directory)
(define-key global-map [(control f5)]  'cscope-find-this-symbol)
(define-key global-map [(control f6)]  'cscope-find-global-definition)
(define-key global-map [(control f7)]  'cscope-find-global-definition-no-prompting)
(define-key global-map [(control f8)]  'cscope-pop-mark)
(define-key global-map [(control f9)]  'cscope-next-symbol)
(define-key global-map [(control f10)] 'cscope-next-file)
(define-key global-map [(control f11)] 'cscope-prev-symbol)
(define-key global-map [(control f12)] 'cscope-prev-file)
(define-key global-map [(meta f9)]     'cscope-display-buffer)
(define-key global-map [(meta f10)]    'cscope-display-buffer-toggle)
(setq cscope-do-not-update-database t)



