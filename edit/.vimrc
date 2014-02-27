set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936   
set termencoding=utf-8   
set encoding=utf-8
set paste 
set tags=/data/haoning/mygit/mynginxmodule/vimtags
"set tags=/data/ts/tstags
"let g:winManagerWindowLayout = "TagList|FileExplorer,BufExplorer"
let g:winManagerWindowLayout = "TagList|FileExplorer"
let g:winManagerWidth = 30
nmap <silent> <F8> :WMToggle<cr>
nmap <silent> <F7> :BufExplorer<cr>
set expandtab
set tabstop=4
set shiftwidth=4
set nu
set cursorline
set fileformats=unix,dos
set ignorecase
set smartcase
set showmatch
highlight Comment ctermfg=LightCyan
nmap <silent> <F9> :cs add /data/haoning/mygit/mynginxmodule/nginx_release/nginx-1.5.6/cscope.out<cr>
nmap <silent> <F10> :cs add /usr/include/cscope.out<cr>
nmap <silent> <F11> :cs kill 0<cr>
nmap <silent> <F12> :cs help<cr>
":cs find s ngx_http_request_t
nmap <C-@>s :cs find s <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>g :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>c :cs find c <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>t :cs find t <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>e :cs find e <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>f :cs find f <C-R>=expand("<cword>")<CR><CR>
nmap <C-@>i :cs find i ^<C-R>=expand("<cword>")<CR>$<CR>
nmap <C-@>d :cs find d <C-R>=expand("<cword>")<CR><CR>
