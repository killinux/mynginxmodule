
(put 'upcase-region 'disabled nil)
(set-language-environment 'utf-8)
(set-keyboard-coding-system 'utf-8)
(set-clipboard-coding-system 'euc-cn)
(set-terminal-coding-system 'utf-8)
(set-buffer-file-coding-system 'euc-cn)
(set-selection-coding-system 'euc-cn)
(modify-coding-system-alist 'process "*" 'utf-8)
(setq default-process-coding-system
            '(euc-cn . euc-cn))
(setq-default pathname-coding-system 'utf-8)

(add-to-list 'load-path "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/auto-complete")  
(require 'auto-complete-config)  
(add-to-list 'ac-dictionary-directories "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/auto-complete/ac-dict")  
(ac-config-default)

(add-to-list 'load-path "/data/haoning/mygit/mynginxmodule/edit/emacs-plugins/c")  
(require 'gccsense)  
(global-set-key "\257" (quote ac-complete-gccsense))
