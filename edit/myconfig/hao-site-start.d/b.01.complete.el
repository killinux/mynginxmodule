(add-to-list 'load-path "/data/haoning/mygit/mynginxmodule/edit/myconfig/myplugin/auto-complete")  
(require 'auto-complete-config)  
(add-to-list 'ac-dictionary-directories "/data/haoning/mygit/mynginxmodule/edit/myconfig/myplugin/auto-complete/ac-dict")  
(ac-config-default)

(load-file "/data/haoning/mygit/mynginxmodule/edit/myconfig/myplugin/gccsense.el")
(require 'gccsense)  
;(global-set-key "\257" (quote ac-complete-gccsense))


(require 'xcscope)
(setq cscope-do-not-update-database t)
