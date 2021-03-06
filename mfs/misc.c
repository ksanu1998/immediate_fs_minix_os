#include "fs.h"
#include <assert.h>
#include <minix/vfsif.h>
#include <minix/bdev.h>
#include "inode.h"
#include "clean.h"

/*===========================================================================*
 *       fs_print_block               *
 *===========================================================================*/
int fs_print_block()
{
  /*
 ino_t inode_nr = fs_m_in.REQ_INODE_NR;
 dev_t dev_nr = fs_m_in.REQ_DEV;
 struct inode *rip;
 block_t b;
 off_t position;
 int block_size;
 
 rip = find_inode(dev_nr, inode_nr);
 
 if((rip->i_mode & I_TYPE) == I_IMMEDIATE){
   printf("This is an IMMEDIATE file.\n");
   return(OK);
 }
 if(rip->i_size == 0){
   printf("File has size 0.\n");
   return(OK);
 }
 block_size = rip->i_sp->s_block_size;
 for(position = 0; position < rip->i_size; position+=block_size){
   b = read_map(rip, position);
   printf("Block: %d\n",b);
 }
 */
 return(OK);
}
/*===========================================================================*
 *				fs_sync					     *
 *===========================================================================*/
int fs_sync()
{
/* Perform the sync() system call.  Flush all the tables. 
 * The order in which the various tables are flushed is critical.  The
 * blocks must be flushed last, since rw_inode() leaves its results in
 * the block cache.
 */
  struct inode *rip;

  assert(lmfs_nr_bufs() > 0);

  /* Write all the dirty inodes to the disk. */
  for(rip = &inode[0]; rip < &inode[NR_INODES]; rip++)
	  if(rip->i_count > 0 && IN_ISDIRTY(rip)) rw_inode(rip, WRITING);

  /* Write all the dirty blocks to the disk. */
  lmfs_flushall();

  return(OK);		/* sync() can't fail */
}


/*===========================================================================*
 *				fs_flush				     *
 *===========================================================================*/
int fs_flush()
{
/* Flush the blocks of a device from the cache after writing any dirty blocks
 * to disk.
 */
  dev_t dev = fs_m_in.m_vfs_fs_flush.device;
  if(dev == fs_dev && lmfs_bufs_in_use() > 0) return(EBUSY);
 
  lmfs_flushall();
  lmfs_invalidate(dev);

  return(OK);
}


/*===========================================================================*
 *				fs_new_driver				     *
 *===========================================================================*/
int fs_new_driver(void)
{
/* Set a new driver endpoint for this device. */
  dev_t dev;
  cp_grant_id_t label_gid;
  size_t label_len;
  char label[sizeof(fs_dev_label)];
  int r;

  dev = fs_m_in.m_vfs_fs_new_driver.device;
  label_gid = fs_m_in.m_vfs_fs_new_driver.grant;
  label_len = fs_m_in.m_vfs_fs_new_driver.path_len;

  if (label_len > sizeof(label))
	return(EINVAL);

  r = sys_safecopyfrom(fs_m_in.m_source, label_gid, (vir_bytes) 0,
	(vir_bytes) label, label_len);

  if (r != OK) {
	printf("MFS: fs_new_driver safecopyfrom failed (%d)\n", r);
	return(EINVAL);
  }

  bdev_driver(dev, label);

  return(OK);
}

int fs_bpeek(void)
{
	return lmfs_do_bpeek(&fs_m_in);
}

