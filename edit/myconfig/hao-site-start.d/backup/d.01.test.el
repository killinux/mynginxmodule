(global-set-key (kbd "C-z t") 'say-hello)
(defun say-hello()(interactive)(print system-type))
;(defun say-hello()(interactive)(print "hello haoning"))


;(require 'tramp)                                                                                                                                                                                             ;(cond                                                                                                                                                                                                        ; ((eq system-type 'windows-nt)                                                                                                                                                                               ;  (setq tramp-default-method "plink"                                                                                                                                                                         ;        tramp-password-end-of-line "\r\n"))                                                                                                                                                                  ; ((eq system-type 'gnu/linux)                                                                                                                                                                                ;  (setq tramp-default-method "ssh")))                                                                                                                                                                        ;(setq tramp-default-user "root"                                                                                                                                                                              ;         tramp-default-host "106.187.88.34")                                                                                                                                                                 ;(setq password-cache-expiry 36000)   