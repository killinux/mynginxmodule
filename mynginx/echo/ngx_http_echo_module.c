/*
 * Copyright (C) Eric Zhang
 */
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
/* Handler function */
	static ngx_int_t
ngx_http_echo_handler(ngx_http_request_t *r)
{
	DEBUG_LOG("haoning haohao .........ngx_http_echo_handler\n");
	ngx_log_stderr(0,"haoning: ngx_http_hello_world_handler\"%s\"","haohao" );
//	ngx_log_error(0,"haoning: ngx_http_hello_world_handler\"%s\"","haohao" );
	fprintf(stderr, "haoning hahahah:%s\r\n","ningning");
        fprintf(stderr,"haoning haohao subrequest in memory: %d\n", (int) r->subrequest_in_memory);
        fprintf(stderr,"haoning haohao  r->method : %d\n",(int) r->method);
        fprintf(stderr,"haoning haohao r->http_version: %d\n",(int) r->http_version) ;
        fprintf(stderr,"haoning haohao r->request_line.data: %s\n",r->request_line.data) ;
        fprintf(stderr,"haoning haohao r->uri.data): %s\n",r->uri.data);
        fprintf(stderr,"haoning haohao r->args.data: %s\n",r->args.data);

    //u_char *mycmd=(u_char *)r->args.data;                                                                                                                              
    //char *urlcmd=(char *) malloc( sizeof(char)*255 );//=(u_char *)r->args.data;                                                                                                                              
    u_char *urlcmd=(u_char *) malloc( sizeof(u_char)*255 );//=(u_char *)r->args.data;                                                                                                                              
    memset(urlcmd,0,sizeof(char)*255);
    strcpy( urlcmd,(u_char *) r->args.data);
    printf("mycmd %s",urlcmd);
    u_char *mycmd=(u_char *) malloc( sizeof(char)*255 );;                                                                                                                            
    ngx_unescape_uri(&mycmd, &urlcmd, 255, NGX_UNESCAPE_REDIRECT);
    fprintf(stderr,"haoning haohao urlcmd:%s\n",urlcmd);
    fprintf(stderr,"haoning haohao mycmd:%s\n",mycmd);
    free(urlcmd);
    free(mycmd);

        fprintf(stderr,"haoning haohao r->unparsed_uri.data: %s\n",r->unparsed_uri.data);
        fprintf(stderr,"haoning haohao r->method_name.data: %s\n",r->method_name.data)  ;
        fprintf(stderr,"haoning haohao r->http_protocol.data: %s\n",r->http_protocol.data);
	fprintf(stderr,"haoning haohao r->exten.data: %s\n",r->exten.data);
        fprintf(stderr,"haoning haohao -----------------: %s\n","end");
	ngx_int_t rc;
	ngx_buf_t *b;
	ngx_chain_t out;
	ngx_http_echo_loc_conf_t *elcf;
	elcf = ngx_http_get_module_loc_conf(r, ngx_http_echo_module);
	if(!(r->method & (NGX_HTTP_HEAD|NGX_HTTP_GET|NGX_HTTP_POST)))
	{
		return NGX_HTTP_NOT_ALLOWED;
	}
	r->headers_out.content_type.len = sizeof("text/html") - 1;
	r->headers_out.content_type.data = (u_char *) "text/html";
	r->headers_out.status = NGX_HTTP_OK;
	r->headers_out.content_length_n = elcf->ed.len;
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
	if(b == NULL)
	{
		ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "Failed to allocate response buffer.");
		return NGX_HTTP_INTERNAL_SERVER_ERROR;
	}
	out.buf = b;
	out.next = NULL;
	b->pos = elcf->ed.data;
	b->last = elcf->ed.data + (elcf->ed.len);
	b->memory = 1;
	b->last_buf = 1;
	rc = ngx_http_send_header(r);
	if(rc != NGX_OK)
	{
		return rc;
	}
	DEBUG_LOG("haoning......ngx_http_output_filter");
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
