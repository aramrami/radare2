#ifndef _INCLUDE_R_CONFIG_H_
#define _INCLUDE_R_CONFIG_H_

#include "r_types.h"
#include "r_util.h"
#include "list.h"

#define CN_BOOL  0x000001
#define CN_INT   0x000002
#define CN_OFFT  0x000004
#define CN_STR   0x000008
#define CN_RO    0x000010
#define CN_RW    0x000020

typedef struct r_config_node_t {
	char *name;
	int hash;
	int flags;
	char *value;
	ut64 i_value;
	ut64 *cb_ptr_q;
	int *cb_ptr_i;
	char **cb_ptr_s;
	int (*callback)(void *user, void *data);
	struct list_head list;
} rConfigNode;

typedef struct r_config_t {
	int lock;
	int last_notfound;
	int n_nodes;
	void *user;
	void (*printf)(const char *str, ...);
	struct list_head nodes;
} rConfig;

#define O struct r_config_t *obj

#ifdef R_API
R_API struct r_config_t *r_config_new(void *user);
R_API int r_config_free(struct r_config_t *cfg);
R_API int r_config_init(struct r_config_t *core, void *user);
R_API void r_config_lock(O, int l);
R_API int r_config_eval(O, const char *str);
R_API struct r_config_node_t *r_config_set_i(O, const char *name, const ut64 i);
R_API struct r_config_node_t *r_config_set_cb(struct r_config_t *cfg, const char *name, const char *value, int (*callback)(void *user, void *data));
R_API struct r_config_node_t *r_config_set_i_cb(struct r_config_t *cfg, const char *name, int ivalue, int (*callback)(void *user, void *data));
R_API int r_config_rm(O, const char *name);
R_API struct r_config_node_t *r_config_set(O, const char *name, const char *value);
R_API ut64 r_config_get_i(O, const char *name);
R_API const char *r_config_get(O, const char *name);
R_API void r_config_list(O, const char *str, int rad);
R_API struct r_config_node_t *r_config_node_get(O, const char *name);
R_API struct r_config_node_t *r_config_node_new(const char *name, const char *value);
R_API int r_config_swap(struct r_config_t *cfg, const char *name);
#endif

#endif
