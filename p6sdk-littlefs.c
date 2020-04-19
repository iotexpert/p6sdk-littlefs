#include "lfs.h"
#include "p6sdk-littlefs.h"
#include "iotexpert-nor.h"

// Read a region in a block. Negative error codes are propogated
// to the user.
 int lfsRead(const struct lfs_config *c, lfs_block_t block,
            lfs_off_t off, void *buffer, lfs_size_t size)
{

    iotexpert_nor_t *nor;
    nor = (iotexpert_nor_t *)c->context;
    size_t length = size;

    cy_rslt_t result = iotexpert_nor_readSync(nor,c->block_size*block+off, buffer, &length);
    if(result == CY_RSLT_SUCCESS)
        return LFS_ERR_OK;
    else
        return LFS_ERR_INVAL;

}

// Program a region in a block. The block must have previously
// been erased. Negative error codes are propogated to the user.
// May return LFS_ERR_CORRUPT if the block should be considered bad.
int lfsProg(const struct lfs_config *c, lfs_block_t block,
            lfs_off_t off, const void *buffer, lfs_size_t size)
{

    iotexpert_nor_t *nor;
    nor = (iotexpert_nor_t *)c->context;
#if 0
    cy_rslt_t  result = cy_serial_flash_qspi_write(c->block_size*block+off, size, buffer);
    if(result == CY_RSLT_SUCCESS)
        return LFS_ERR_OK;
    else
        return LFS_ERR_INVAL;
#endif    
}

// Erase a block. A block must be erased before being programmed.
// The state of an erased block is undefined. Negative error codes
// are propogated to the user.
// May return LFS_ERR_CORRUPT if the block should be considered bad.
int lfsErase(const struct lfs_config *c, lfs_block_t block)
{

    iotexpert_nor_t *nor;
    nor = (iotexpert_nor_t *)c->context;
#if 0
    cy_rslt_t rslt = cy_serial_flash_qspi_erase(c->block_size*block,c->block_size);
    if(rslt == CY_RSLT_SUCCESS)
        return LFS_ERR_OK;
    else
    {
        return LFS_ERR_CORRUPT;
    }
#endif   
    
}

// Sync the state of the underlying block device. Negative error codes
// are propogated to the user.
int lfsSync(const struct lfs_config *c)
{

    iotexpert_nor_t *nor;
    nor = (iotexpert_nor_t *)c->context;

    return LFS_ERR_OK;

}



int lfsInitConfig(struct lfs_config *cfg)
{

    iotexpert_nor_t *nor;
    nor = (iotexpert_nor_t *)cfg->context;

    // block device operations
    cfg->read  = lfsRead;
    cfg->prog  = lfsProg;
    cfg->erase = lfsErase;
    cfg->sync  = lfsSync;

    // block device configuration
    cfg->read_size       = 16;
    cfg->prog_size       = 16;
    cfg->block_size      = 256*1024;            // 256 kbytes per sector

    cfg->block_count     = 256;                 // 256 * 256 kb = 64mbytes 
    cfg->cache_size      = 16;
    cfg->lookahead_size  = 16;
    cfg->block_cycles    = 500;

    return LFS_ERR_OK;
}