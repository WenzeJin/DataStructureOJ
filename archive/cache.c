#include "memory/mmu/cache.h"
#define CACHESIZE 1024                      //2^10
#define SLOTSIZE 64                         //2^6
#define BLOCKSIZE 8                         //2^3
#define BLOCKNUM CACHESIZE / BLOCKSIZE      //2^7
#define MEMSIZE 128 * 1024 * 1024           //2^27
#include<stdlib.h>

struct CacheBlock {
    bool valid_bit;
    uint32_t tag;                   //can be uint16_t
    uint8_t buff[SLOTSIZE];
};

struct CacheBlock caches[CACHESIZE];

extern uint8_t hw_mem[MEMSIZE];

/*
8-way set associative
write through
not write allocate
random
|tag:14bit|block_index:7bit|slot_bias:6bit|
*/

uint32_t block_index;
uint32_t slot_bias;
uint32_t tag;

void cache_addr_cal(paddr_t paddr) {
    slot_bias = paddr % SLOTSIZE;
    block_index = ((paddr / SLOTSIZE) % BLOCKSIZE) * 8;
    tag = paddr / (SLOTSIZE * BLOCKSIZE);
}

paddr_t mem_block_start(paddr_t paddr) {
    return paddr & 0xffffffc0;
}

// init the cache
void init_cache()
{
    srand(time(0));
	for(int i = 0; i < CACHESIZE; i++) {
	    caches[i].valid_bit = false;
	}
}

// write data to cache
void cache_write(paddr_t paddr, size_t len, uint32_t data)
{
	assert(len == 1 || len == 2 || len == 4);
	cache_addr_cal(paddr);
	size_t len1 = (SLOTSIZE - slot_bias < len) ? SLOTSIZE - slot_bias : len;
	size_t len2 = (len1 < len) ? len - len1 : 0;
	uint8_t in_buff[4];
	short buff_ind = 0;
	memcpy(in_buff, &data, len);
	
	for(int i = 0; i < BLOCKSIZE; i++) {    //在block中遍历
	    uint32_t pos = block_index + i;     
	    if(caches[pos].tag == tag) {
	        if(caches[pos].valid_bit == true) {
	            //hit1
	            for(int j = 0; j < len1; j++) {
	                caches[pos].buff[slot_bias + j] = in_buff[buff_ind];
	                buff_ind++;
	            }
	            break;
	        }
	    }
	}
	if(len2) {
	    cache_addr_cal(paddr + len1);
	    buff_ind = len1;
	    for(int i = 0; i < BLOCKSIZE; i++) {
	        uint32_t pos = block_index + i;
    	    if(caches[pos].tag == tag) {
    	        if(caches[pos].valid_bit == true) {
    	            //hit2
    	            for(int j = 0; j < len2; j++) {
    	                caches[pos].buff[slot_bias + j] = in_buff[buff_ind];
	                    buff_ind++;
    	            }
    	            break;
    	        }
    	    }
    	}
	}
	
	memcpy(hw_mem + paddr, &data, len);
	return;
}

// read data from cache
uint32_t cache_read(paddr_t paddr, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	bool hit1, hit2;
	uint32_t index1, index2;
	cache_addr_cal(paddr);
	size_t len1 = (SLOTSIZE - slot_bias < len) ? SLOTSIZE - slot_bias : len;
	size_t len2 = (len1 < len) ? len - len1 : 0;
	uint8_t re_buff[4];
	short buff_ind = 0;
	uint32_t result = 0;
	
RETRY:
    hit1 = false, hit2 = false, buff_ind = 0;
    cache_addr_cal(paddr);
	for(int i = 0; i < BLOCKSIZE; i++) {
	    uint32_t pos = block_index + i;
	    if(caches[pos].tag == tag) {
	        if(caches[pos].valid_bit == true) {
	            //hit1
	            hit1 = true;
	            index1 = i;
	            for(int j = 0; j < len1; j++) {
	                re_buff[buff_ind] = caches[pos].buff[slot_bias + j];
	                buff_ind++;
	            }
	            break;
	        }
	    }
	}
	if(len2) {
	    cache_addr_cal(paddr + len1);
	    buff_ind = len1;
	    for(int i = 0; i < BLOCKSIZE; i++) {
	        uint32_t pos = block_index + i;
    	    if(caches[pos].tag == tag) {
    	        if(caches[pos].valid_bit == true) {
    	            //hit2
    	            hit2 = true;
    	            index2 = i;
    	            for(int j = 0; j < len2; j++) {
    	                re_buff[buff_ind] = caches[pos].buff[slot_bias + j];
	                    buff_ind++;
    	            }
    	            break;
    	        }
    	    }
    	}
	}
	if(!hit1 || (len2 && !hit2)) goto FAIL;
	memcpy(&result, re_buff, len);
	return result;
	
FAIL:
    if(!hit1) {
        index1 = rand() % 8;
        cache_addr_cal(paddr);
        uint32_t pos = block_index + index1;
        memcpy(caches[pos].buff, hw_mem + mem_block_start(paddr), 64);
        caches[pos].tag = tag;
        caches[pos].valid_bit = true;
    }
    if(len2 && !hit2) {
        index2 = rand() % 8;
        while(index2 == index1) {
            index2 = rand() % 8;
        }
        cache_addr_cal(paddr + len1);
        uint32_t pos = block_index + index2;
        memcpy(caches[pos].buff, hw_mem + mem_block_start(paddr) + 64, 64);
        caches[pos].tag = tag;
        caches[pos].valid_bit = true;
    }
    goto RETRY;
}

