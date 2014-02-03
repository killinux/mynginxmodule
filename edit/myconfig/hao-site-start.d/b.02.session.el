(load-file "/data/haoning/mygit/mynginxmodule/edit/myconfig/myplugin/session.el")   
(require 'session)   
(add-hook 'after-init-hook 'session-initialize)   
;(require 'doxymacs)                                                                                                                                                                                           

(global-set-key [(f5)] 'speedbar)   

(require 'ibuffer)   
(global-set-key (kbd "C-x C-b") 'ibuffer)   

(require 'ido)   
(ido-mode t)   

(load-file "/data/haoning/mygit/mynginxmodule/edit/myconfig/myplugin/tabbar.el")   
(require 'tabbar)   
(tabbar-mode 1)   
(global-set-key [(meta j)] 'tabbar-backward)   
(global-set-key [(meta k)] 'tabbar-forward) 