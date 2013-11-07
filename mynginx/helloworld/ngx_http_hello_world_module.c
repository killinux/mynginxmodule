#include <ngx_config.h> 
#include <ngx_core.h> 
#include <ngx_http.h> 
#include <ngx_buf.h> 
#include <ngx_log.h>
static  char *ngx_http_hello_world(ngx_conf_t *cf ,ngx_command_t *cmd,void *conf); 
//*cf 指向ngx_conf_t 结构体指针，从指令后面传过来的参数 
//*cmd 指向当前结构体ngx_command_t 的指针(互相指) 
//*conf指向自定义模块配置结构体的指针 
//cf: 该参数里面保存里读取到的配置信息的原始字符串以及相关的一些信息。特别注意的是这个参数的args字段是一个ngx_str_t类型的数组，每个数组元素。该数组的首个元素是这个配置指令本身的字符串，第二个元素是首个参数，第三个元素是第二个参数，依次类推。
//cmd: 这个配置指令对应的ngx_command_t结构。
//conf: 就是定义的存储这个配置值的结构体，比如在上面展示的那个ngx_http_hello_loc_conf_t。当解析这个hello_string变量的时候，传入的conf就指向一个ngx_http_hello_loc_conf_t类型的变量。用户在处理的时候可以使用类型转换，转换成自己知道的类型，再进行字段的赋值。
static ngx_command_t ngx_http_hello_world_commands[]={ 
        { 
                ngx_string("hello_world"),//指令名称，nginx.conf中使用 
                NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,  //注释1 
                ngx_http_hello_world,//回调函数 ，上面定义的带三个参数 
                0,//保持的值放的位置：全局，server，location 
                0,//指令的值保存的位置 
                NULL //一般都为NULL 
        }, 
        ngx_null_command  //读入ngx_null_command 指令后停止 
}; 
static u_char ngx_hello_world[]="hello world"; 
//ngx_http_<module name>_module_ctx用于创建和合并三个配置 
//参考http/ngx_http_config.h 
static ngx_http_module_t ngx_http_hello_world_module_ctx={ 
        NULL,//preconfiguration 
        NULL,//postconfiguration 
        NULL,//create main configuration 
        NULL,//init main configuration 
        NULL,//create server configuration 
        NULL,//merge server configuration 
        NULL,//create location configuration 
        NULL //merge localtion configuration 
}; 
//nginx进程，线程相关，ngx_http_<module name>_module 
//这个模块的定义是把数据处理关联到特定模块的关键 
ngx_module_t ngx_http_hello_world_module={ 
        NGX_MODULE_V1, 
        &ngx_http_hello_world_module_ctx,//module context 
        ngx_http_hello_world_commands,  //module directives 
        NGX_HTTP_MODULE,                //module type 
        NULL,         //init master 
        NULL,         //init module 
        NULL,         //init process 
        NULL,         //init thread 
        NULL,         //exit thread 
        NULL,         //exit process 
        NULL,         //exit master 
        NGX_MODULE_V1_PADDING 
}; 
static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r) 
{ 
	ngx_log_stderr(0, "haoning: ngx_http_hello_world_handler\"%s\"","haohao" );
        ngx_buf_t *b; 
        ngx_chain_t out; 

        r->headers_out.content_type.len =sizeof("text/plain")-1; 
        r->headers_out.content_type.data=(u_char *) "text/plain"; 

        b=ngx_pcalloc(r->pool,sizeof(ngx_buf_t)); 

        out.buf=b; 
        out.next=NULL; 

        b->pos=ngx_hello_world; 
        b->last=ngx_hello_world+sizeof(ngx_hello_world); 
        b->memory=1; 
        b->last_buf=1; 

        r->headers_out.status=NGX_HTTP_OK; 
        r->headers_out.content_length_n=sizeof(ngx_hello_world); 
        ngx_http_send_header(r); 

        return ngx_http_output_filter(r,&out); 
} 
//回调函数，1获得location中的“核心”结构体，2为他分配个处理函数 
static char *ngx_http_hello_world(ngx_conf_t *cf,ngx_command_t *cmd,void *conf) 
{ 
	ngx_log_stderr(0, "haoning: \"%s\"","haohao" );
        ngx_http_core_loc_conf_t *clcf; 

        clcf=ngx_http_conf_get_module_loc_conf(cf,ngx_http_core_module); 
        clcf->handler=ngx_http_hello_world_handler; 
        return NGX_CONF_OK; 
} 
