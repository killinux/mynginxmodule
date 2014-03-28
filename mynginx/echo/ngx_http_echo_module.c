#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <time.h>
#include "haolog.h"
#include <ngx_log.h>
/* Module config */
typedef struct {
	ngx_str_t  ed;
} ngx_http_echo_loc_conf_t;
static char *ngx_http_echo(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static void *ngx_http_echo_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_echo_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child);
/* Directives */
static ngx_command_t  ngx_http_echo_commands[] = {
	{ 
		ngx_string("echo"),
		NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
		ngx_http_echo,
		NGX_HTTP_LOC_CONF_OFFSET,
		offsetof(ngx_http_echo_loc_conf_t, ed),
		NULL 
	},
	ngx_null_command
};
/* Http context of the module */
static ngx_http_module_t  ngx_http_echo_module_ctx = {
	NULL,                                  /* preconfiguration */
	NULL,                                  /* postconfiguration */
	NULL,                                  /* create main configuration */
	NULL,                                  /* init main configuration */
	NULL,                                  /* create server configuration */
	NULL,                                  /* merge server configuration */
	ngx_http_echo_create_loc_conf,         /* create location configration */
	ngx_http_echo_merge_loc_conf           /* merge location configration */
};
/* Module */
ngx_module_t  ngx_http_echo_module = {
	NGX_MODULE_V1,
	&ngx_http_echo_module_ctx,             /* module context */
	ngx_http_echo_commands,                /* module directives */
	NGX_HTTP_MODULE,                       /* module type */
	NULL,                                  /* init master */
	NULL,                                  /* init module */
	NULL,                                  /* init process */
	NULL,                                  /* init thread */
	NULL,                                  /* exit thread */
	NULL,                                  /* exit process */
	NULL,                                  /* exit master */
	NGX_MODULE_V1_PADDING
};
void hao_urldecode(char *dest, const char *src)//why not **
{
    const char *p = src;
    char code[3] = {0};
    unsigned long ascii = 0;
    char *end = NULL;
    while(*p)
    {   
        if(*p == '%')
        {   
            memcpy(code, ++p, 2); 
            ascii = strtoul(code, &end, 16);
            *dest++ = (char)ascii;
            p += 2;
        }   
        else
            *dest++ = *p++;
    }   
}
int mysystem(char* cmdstring, char* buf, int len)
{
    fprintf(stderr,"haoning haohao -----------------: %s\n","mysystem");
    int   fd[2];
    pid_t pid;
    int   n, count; 
    memset(buf, 0, len);
    if (pipe(fd) < 0)
        return -1; 
    if ((pid = fork()) < 0)
        return -1; 
    else if (pid > 0)     /* parent process */
    {   
        fprintf(stderr,"haoning haohao -----------------: %s\n","mysystem parent");
        close(fd[1]);     /* close write end */
        count = 0;
        while ((n = read(fd[0], buf + count, len)) > 0 && count > len)
            count += n;
        close(fd[0]);
        if (waitpid(pid, NULL, 0) > 0)
            return -1; 
    }   
    else                  /* child process */
    {   
        fprintf(stderr,"haoning haohao -----------------: %s\n","mysystem child");
        close(fd[0]);     /* close read end */
        if (fd[1] != STDOUT_FILENO)
        {   
            if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
            {   
                return -1; 
            }   
            close(fd[1]);
        }   
        if (execl("/bin/sh", "sh", "-c", cmdstring, (char*)0) == -1) 
            return -1; 
    }   
    return 0;
}
/* Handler function */
	static ngx_int_t
ngx_http_echo_handler(ngx_http_request_t *r)
{
    DEBUG_LOG("haoning haohao .........ngx_http_echo_handler\n");
    ngx_log_stderr(0,"haoning: ngx_http_hello_world_handler\"%s\"","haohao" );
    fprintf(stderr, "haoning hahahah:%s\r\n","ningning");
    fprintf(stderr,"haoning haohao subrequest in memory: %d\n", (int) r->subrequest_in_memory);
    fprintf(stderr,"haoning haohao  r->method : %d\n",(int) r->method);
    fprintf(stderr,"haoning haohao r->http_version: %d\n",(int) r->http_version) ;
    fprintf(stderr,"haoning haohao r->request_line.data: %s\n",r->request_line.data) ;
    fprintf(stderr,"haoning haohao r->uri.data): %s\n",r->uri.data);
    fprintf(stderr,"haoning haohao r->args.data: %s\n",r->args.data);

    char *urlcmd;                                                                                                                             
    urlcmd=(char *)malloc(1024*sizeof(char));
    memset(urlcmd,0,sizeof(char)*1024);
    char *mycmd=(char *)r->args.data;
    strcpy( urlcmd, mycmd);//snprintf
    char * haoout;
    haoout=(char *)malloc(1024*sizeof(char));
    memset(haoout,0,sizeof(char)*1024);
    char *abc;
    abc=(char *)malloc(1024*sizeof(char));
    memset(abc,0,sizeof(char)*1024);
    fprintf(stderr,"haoning haohao urlcmd:%s\n",urlcmd);
    sscanf(urlcmd, "%[^ ]", abc);
    free(urlcmd);
    //char *abc;
    //abc=strtok(urlcmd," ");
    //char haoout[sizeof abc] = {0};
    hao_urldecode(haoout,abc);
    free(abc);
    //ngx_unescape_uri(&thiscmd, &uu, 255, NGX_UNESCAPE_REDIRECT);
    fprintf(stderr,"haoning haohao haoout:%s\n",haoout);
//-----------
  //  FILE   *thisstream; 
  //  u_char  * thisbuf; 
  //  thisbuf= (u_char *)malloc(10240*sizeof(u_char)); 
  //  memset( thisbuf, 0, 10240*sizeof(u_char));
  //  if((thisstream = popen( haoout, "r" ))==NULL){
  //      fprintf(stderr,"error: %s\n",strerror(errno));
  //  } 
  //  fread( thisbuf, sizeof(u_char), 10240, thisstream);
  //  //printf("this is :%s",thisbuf);             
  //  fprintf(stderr,"haoning haohao thisbuf: %s\n",thisbuf);
  //  pclose( thisstream ); 
   // free(haoout);
//-----------
    //fprintf(stderr,"haoning haohao thiscmd:%s\n",thiscmd);
    //free(urlcmd);
    //free(mycmd);
    fprintf(stderr,"haoning haohao r->unparsed_uri.data: %s\n",r->unparsed_uri.data);
    fprintf(stderr,"haoning haohao r->method_name.data: %s\n",r->method_name.data)  ;
    fprintf(stderr,"haoning haohao r->http_protocol.data: %s\n",r->http_protocol.data);
  //  fprintf(stderr,"haoning haohao r->exten.data: %s\n",r->exten.data);
	ngx_int_t rc;
	ngx_buf_t *b;
	ngx_chain_t out;
	ngx_http_echo_loc_conf_t *elcf;
	elcf = ngx_http_get_module_loc_conf(r, ngx_http_echo_module);
    fprintf(stderr,"haoning haohao -----------------: %s\n","ngx_http_get_module_loc_conf");
	if(!(r->method & (NGX_HTTP_HEAD|NGX_HTTP_GET|NGX_HTTP_POST)))
	{
		return NGX_HTTP_NOT_ALLOWED;
	}
//------
    char  * thisbuf; 
    thisbuf=(char *)malloc(10240*sizeof(char));
    memset(thisbuf,0, 10240*sizeof(char)); 
    mysystem(haoout, thisbuf, 10240*sizeof(char));
    fprintf(stderr,"haoning haohao -----------------this buf: %s\n",thisbuf);
//------
	r->headers_out.content_type.len = sizeof("text/html") - 1;//去掉\0
	r->headers_out.content_type.data = (u_char *) "text/html";
	r->headers_out.status = NGX_HTTP_OK;
	//r->headers_out.content_length_n = elcf->ed.len;
	//r->headers_out.content_length_n = 10240*sizeof(u_char);//strlen(thisbuf);
	r->headers_out.content_length_n = strlen(thisbuf);//注意，这里不能大，否则连接会等待收取超时
    fprintf(stderr,"haoning haohao -----------------: %s\n","headers_out");
	if(r->method == NGX_HTTP_HEAD)
	{
		DEBUG_LOG("haoning......ngx_http_echo_handlerr---r->method == NGX_HTTP_HEAD");
		rc = ngx_http_send_header(r);
		if(rc != NGX_OK)
		{
			return rc;
		}
	}
	b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    fprintf(stderr,"haoning haohao -----------------: %s\n","ngx_pcalloc");
	if(b == NULL)
	{
		ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "Failed to allocate response buffer.");
		return NGX_HTTP_INTERNAL_SERVER_ERROR;
	}
	out.buf = b;
	out.next = NULL;
	//u_char * hh;
    //hh =(u_char *)"hello hao123";// elcf->ed.data;
	//b->pos =hh;// elcf->ed.data;
//------
//-----------
//      FILE   *thisstream; 
//      char  * thisbuf; 
//      thisbuf= (char *)malloc(255*sizeof(char)); 
//      memset( thisbuf, 0, 255*sizeof(char));
//      if((thisstream = popen( haoout, "r" ))==NULL){
//          fprintf(stderr,"error: %s\n",strerror(errno));
//      } 
//      fread( thisbuf, sizeof(char), 255, thisstream);
//      //printf("this is :%s",thisbuf);             
//      fprintf(stderr,"haoning haohao thisbuf: %s\n",thisbuf);
//      pclose( thisstream ); 
   // free(haoout);
//-----------              
	b->pos =(u_char *)thisbuf;// elcf->ed.data;
	//b->last = elcf->ed.data + (elcf->ed.len);
	//b->last = elcf->ed.data + 10240*sizeof(u_char);
	//b->last = elcf->ed.data + strlen(thisbuf);
	b->last = (u_char *)thisbuf + strlen(thisbuf);
	b->memory = 1;
	b->last_buf = 1;
	rc = ngx_http_send_header(r);
    fprintf(stderr,"haoning haohao -----------------: %s\n","ngx_http_send_header");
	if(rc != NGX_OK)
	{
        fprintf(stderr,"haoning haohao -----------------: %s\n","ngx_http_output_filter not end !");
		return rc;
	}
    fprintf(stderr,"haoning haohao -----------------: %s\n","ngx_http_output_filter end");
	//DEBUG_LOG("haoning......ngx_http_output_filter");
	return ngx_http_output_filter(r, &out);
}
	static char *
ngx_http_echo(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
	DEBUG_LOG("haoning --ngx_http_echo->>>>> init");
	ngx_http_core_loc_conf_t  *clcf;
	clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
	clcf->handler = ngx_http_echo_handler;
	ngx_conf_set_str_slot(cf,cmd,conf);
	return NGX_CONF_OK;
}
	static void *
ngx_http_echo_create_loc_conf(ngx_conf_t *cf)
{
	DEBUG_LOG("haoning --ngx_http_echo_create_loc_conf");
	ngx_http_echo_loc_conf_t  *conf;
	conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_echo_loc_conf_t));
	if (conf == NULL) {
		return NGX_CONF_ERROR;
	}
	conf->ed.len = 0;
	conf->ed.data = NULL;
	return conf;
}
	static char *
ngx_http_echo_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
	DEBUG_LOG("haoning --ngx_http_echo_merge_loc_conf");
	ngx_http_echo_loc_conf_t *prev = parent;
	ngx_http_echo_loc_conf_t *conf = child;
	ngx_conf_merge_str_value(conf->ed, prev->ed, "");
	return NGX_CONF_OK;
}
