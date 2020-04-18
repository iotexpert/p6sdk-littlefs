#include "lfs.h"
#include "p6sdk-littlefs.h"


// Read a region in a block. Negative error codes are propogated
// to the user.
 int lfsRead(const struct lfs_config *c, lfs_block_t block,
            lfs_off_t off, void *buffer, lfs_size_t size)
{
#if 0
    cy_rslt_t result = cy_serial_flash_qspi_read(c->block_size*block+off, size, buffer);
    if(result == CY_RSLT_SUCCESS)
        return LFS_ERR_OK;
    else
        return LFS_ERR_INVAL;
#endif

}

// Program a region in a block. The block must have previously
// been erased. Negative error codes are propogated to the user.
// May return LFS_ERR_CORRUPT if the block should be considered bad.
int lfsProg(const struct lfs_config *c, lfs_block_t block,
            lfs_off_t off, const void *buffer, lfs_size_t size)
{
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
    return LFS_ERR_OK;

}



int lfsInitConfig(struct lfs_config *cfg)
{
    
    // block device operations
    cfg->read  = lfsRead;
    cfg->prog  = lfsProg;
    cfg->erase = lfsErase;
    cfg->sync  = lfsSync;

    // block device configuration
    cfg->read_size       = 16;
    cfg->prog_size       = 16;
    cfg->block_size      = 256*1024;             // 256 kbytes per sector
    cfg->block_count     = 256;                 // 256 * 256 kb = 64mbytes 
    cfg->cache_size      = 16;
    cfg->lookahead_size  = 16;
    cfg->block_cycles    = 500;

    return LFS_ERR_OK;
}