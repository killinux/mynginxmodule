(load-file "/data/haoning/mygit/mynginxmodule/edit/myconfig/myplugin/cedet-1.0.1/common/cedet.el")
(require 'cedet)

(add-to-list 'load-path "/data/haoning/mygit/mynginxmodule/edit/myconfig/myplugin/ecb-2.40")
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

(global-set-key (kbd "C-z 1") 'ecb-maximize-window-directories)
(global-set-key (kbd "C-z 2") 'ecb-maximize-window-sources)
(global-set-key (kbd "C-z 3") 'ecb-maximize-window-methods)
(global-set-key (kbd "C-z 4") 'ecb-maximize-window-history)
(global-set-key (kbd "C-z r") 'ecb-restore-default-window-sizes)
(global-set-key (kbd "C-z C-b") 'windmove-left)
(global-set-key (kbd "C-z C-f") 'windmove-right)
(global-set-key (kbd "C-z C-p") 'windmove-up)
(global-set-key (kbd "C-z C-n") 'windmove-down)

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
