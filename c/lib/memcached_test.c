#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "libmemcached/memcached.h"
//gcc -o cc cc.c  -L /usr/local/lib -lmemcached
void test1()
{

	printf("memcache test");
	memcached_st *memc;
	memcached_return rc;
	memcached_server_st *servers;
	char value[8191];
	printf("memcache test");
	//connect multi server
	memc = memcached_create(NULL);
	servers = memcached_server_list_append(NULL, "localhost", 11211, &rc);
	//servers = memcached_server_list_append(servers, "localhost", 11212, &rc);
	rc = memcached_server_push(memc, servers);
	memcached_server_free(servers);
	printf("memcache test");
	//Save multi data
	size_t i;
	char *keys[]= {"key1" "key2", "key3"};
	size_t key_length[]= {4, 4, 4};
	char *values[] = {"This is c first value", "This is c second value", "This is c third value"};
	size_t val_length[]= {21, 22, 21};
	for (i=0; i < 3; i++)
	{
		rc = memcached_set(memc, keys[i],
				key_length[i], values[i], val_length[i], (time_t)180,
				(uint32_t)0);
		if (rc == MEMCACHED_SUCCESS)
		{
			printf("Save key:%s data:%s success.n",keys[i], values[i]);
		}
	}

	char return_key[MEMCACHED_MAX_KEY];
	size_t return_key_length;
	char *return_value;
	size_t return_value_length;
	uint32_t flags;
	rc = memcached_mget(memc, (const char * const*)keys, key_length, 3);
	while ((return_value = memcached_fetch(memc, return_key,&return_key_length, &return_value_length, &flags, &rc))) {
		if (rc == MEMCACHED_SUCCESS)
		{
			printf("Fetch key:%s data:%sn", return_key, return_value);
		}
	}
	//Delete multi data
	for (i=0; i < 3; i++)
	{
		rc = memcached_set(memc, keys[i], key_length[i],
				values[i], val_length[i], (time_t)180, (uint32_t)0);
		rc = memcached_delete(memc, keys[i],
				key_length[i], (time_t)0);
		if (rc == MEMCACHED_SUCCESS)
		{
			printf("Delete %s %s successn", keys[i], values[i]);
		}
	}
	//free
	memcached_free(memc);

}
void test2()
{

	 //memcached_servers_parse (char *server_strings); 
  memcached_server_st *servers = NULL;
  memcached_st *memc;
  memcached_return rc;
  char *key= "keystring";
  char *value= "keyvalue";
  memc= memcached_create(NULL);
  servers= memcached_server_list_append(servers, "localhost", 11211, &rc);   
  rc= memcached_server_push(memc, servers);

  if (rc == MEMCACHED_SUCCESS)
    fprintf(stderr,"Added server successfully\n");   
  else
    fprintf(stderr,"Couldn't add server: %s\n",memcached_strerror(memc, rc));

  rc= memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)0, (uint32_t)0);

  if (rc == MEMCACHED_SUCCESS)
    fprintf(stderr,"Key stored successfully\n");   
  else
    fprintf(stderr,"Couldn't store key: %s\n",memcached_strerror(memc, rc));
  char *new_value = NULL;
  size_t len = 0;
  new_value =  memcached_get(memc, key, strlen(key),&len,(uint32_t)0, &rc); 
  if(new_value != NULL)
  {
	printf("value: %s %ld\n", new_value, len);
  }
}
int main(int argc, char *argv[])
{
	test2();
	return 0;
}
