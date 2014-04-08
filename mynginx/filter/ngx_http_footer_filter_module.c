#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
//缩进使用4个空格
typedef struct {
    ngx_hash_t                types;
    ngx_array_t              *types_keys;
//不同的段落间空两行
    ngx_http_complex_value_t *variable;
} ngx_http_footer_loc_conf_t;
//静态函数先声明后定义
typedef struct {
    ngx_str_t                 footer;
//每行长度最大80字符，超出需要换行
} ngx_http_footer_ctx_t;
 
static char *ngx_http_footer_filter(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static void *ngx_http_footer_create_loc_conf(ngx_conf_t *cf);

static char *ngx_http_footer_merge_loc_conf(ngx_conf_t *cf,void *parent, void *child);
static ngx_int_t ngx_http_footer_filter_init(ngx_conf_t *cf);
 
static ngx_command_t  ngx_http_footer_filter_commands[] = {
    { ngx_string("footer"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_http_footer_filter,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },
 
    { ngx_string("footer_types"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_1MORE,
      ngx_http_types_slot,
      NGX_HTTP_LOC_CONF_OFFSET,
      offsetof(ngx_http_footer_loc_conf_t, types_keys),
      &ngx_http_html_default_types[0] },
      ngx_null_command
};
 
static ngx_http_module_t  ngx_http_footer_filter_module_ctx = {
    NULL,                                             
    ngx_http_footer_filter_init,                      
 
    NULL,                                             
    NULL,                                             
 
    NULL,                                             
    NULL,                                             
 
    ngx_http_footer_create_loc_conf,                  
    ngx_http_footer_merge_loc_conf                    
};
 
ngx_module_t  ngx_http_footer_filter_module = {
    NGX_MODULE_V1,
    &ngx_http_footer_filter_module_ctx,               
    ngx_http_footer_filter_commands,                  
    NGX_HTTP_MODULE,                                  
    NULL,                                             
    NULL,                                              
    NULL,                                             
    NULL,                                             
    NULL,                                              
    NULL,                                             
    NULL,                                             
    NGX_MODULE_V1_PADDING
};
 
static ngx_http_output_header_filter_pt  ngx_http_next_header_filter;
static ngx_http_output_body_filter_pt    ngx_http_next_body_filter;
 
 
//函数定义，返回值后换行。
static ngx_int_t
ngx_http_footer_header_filter(ngx_http_request_t *r)
{
    ngx_http_footer_ctx_t       *ctx;
    ngx_http_footer_loc_conf_t  *lcf;
 
    lcf = ngx_http_get_module_loc_conf(r, ngx_http_footer_filter_module);
//换行后操作符在行首
    if (lcf->variable == (ngx_http_complex_value_t *) -1
        || r->header_only
        || r != r->main
        || r->headers_out.status == NGX_HTTP_NO_CONTENT
//条件分行，大括号另起一行
        || ngx_http_test_content_type(r, &lcf->types) == NULL)
    {
        return ngx_http_next_header_filter(r);
    }
 
    ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_footer_ctx_t));
    if(ctx == NULL) {
       return NGX_ERROR;
    }
 
    if (ngx_http_complex_value(r, lcf->variable, &ctx->footer) != NGX_OK) {
        return NGX_ERROR;
    }
 
    ngx_http_set_ctx(r, ctx, ngx_http_footer_filter_module);
 
    if (r->headers_out.content_length_n != -1) {
        r->headers_out.content_length_n += ctx->footer.len;
    }
 
    if (r->headers_out.content_length) {
        r->headers_out.content_length->hash = 0;
        r->headers_out.content_length = NULL;
    }
 
    ngx_http_clear_accept_ranges(r);
 
    return ngx_http_next_header_filter(r);
}
 
static ngx_int_t
ngx_http_footer_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
//局部变量定义，类型名短的在前。变量名对齐，“*”不算在变量名中。
{
    ngx_buf_t             *buf;
    ngx_uint_t             last;
    ngx_chain_t           *cl, *nl;
    ngx_http_footer_ctx_t *ctx;
    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http footer body filter");
    ctx = ngx_http_get_module_ctx(r, ngx_http_footer_filter_module);
    if (ctx == NULL) {
        return ngx_http_next_body_filter(r, in);
    }
    last = 0;
    for (cl = in; cl; cl = cl->next) {
         if (cl->buf->last_buf) {
             last = 1;
             break;
         }
    }
 
    if (!last) {
        return ngx_http_next_body_filter(r, in);
    }
 
    buf = ngx_calloc_buf(r->pool);
    if (buf == NULL) {
        return NGX_ERROR;
    }
 
    nl = ngx_alloc_chain_link(r->pool);
    if (nl == NULL) {
        return NGX_ERROR;
    }
 
    buf->pos = ctx->footer.data;
    buf->last = buf->pos + ctx->footer.len;
    buf->start = buf->pos;
    buf->end = buf->last;
    buf->last_buf = 1;
    buf->memory = 1;
 
    nl->buf = buf;
    nl->next = NULL;
    cl->next = nl;
    cl->buf->last_buf = 0;
 
    return ngx_http_next_body_filter(r, in);
}
 
 
static char *
ngx_http_footer_filter(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    fprintf(stderr,"haoning haohao -----------------: %s\n","ngx_http_footer_filter");
    ngx_str_t                    *value;
    ngx_http_complex_value_t    **cv;
 
    cv = &((ngx_http_footer_loc_conf_t *) conf)->variable;
 
    if (*cv != NULL) {
        return "duplicate";
    }
 
    value = cf->args->elts;
    if ((value + 1)->len) {
        cmd->offset = offsetof(ngx_http_footer_loc_conf_t, variable);
        return ngx_http_set_complex_value_slot(cf, cmd, conf);
    }
 
    *cv = (ngx_http_complex_value_t *) -1;
 
    return NGX_OK;
 
}
 
 
static void *
ngx_http_footer_create_loc_conf(ngx_conf_t *cf)
{
    ngx_http_footer_loc_conf_t  *conf;
 
    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_footer_loc_conf_t));
    if (conf == NULL) {
        return NULL;
    }
 
    return conf;
}
 
 
static char *
ngx_http_footer_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_footer_loc_conf_t  *prev = parent;
    ngx_http_footer_loc_conf_t  *conf = child;
 
    if (ngx_http_merge_types(cf, &conf->types_keys, &conf->types,
                             &prev->types_keys,&prev->types,
                             ngx_http_html_default_types)
        != NGX_OK)
    {
       return NGX_CONF_ERROR;
    }
 
    if (conf->variable == NULL) {
        conf->variable = prev->variable;
    }
 
    if (conf->variable == NULL) {
        conf->variable = (ngx_http_complex_value_t *) -1;
    }
 
    return NGX_CONF_OK;
}
 
 
static ngx_int_t
ngx_http_footer_filter_init(ngx_conf_t *cf)
{
    ngx_http_next_body_filter = ngx_http_top_body_filter;
    ngx_http_top_body_filter = ngx_http_footer_body_filter;
 
    ngx_http_next_header_filter = ngx_http_top_header_filter;
    ngx_http_top_header_filter = ngx_http_footer_header_filter;
 
    return NGX_OK;
}
