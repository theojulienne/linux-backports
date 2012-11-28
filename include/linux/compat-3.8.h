#ifndef LINUX_3_8_COMPAT_H
#define LINUX_3_8_COMPAT_H

#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3,8,0))

/* This backports:
 *
 * commit 4b20db3de8dab005b07c74161cb041db8c5ff3a7
 * Author: Thomas Hellstrom <thellstrom@vmware.com>
 * Date:   Tue Nov 6 11:31:49 2012 +0000
 *
 *	kref: Implement kref_get_unless_zero v3
 */
/**
 * kref_get_unless_zero - Increment refcount for object unless it is zero.
 * @kref: object.
 *
 * Return non-zero if the increment succeeded. Otherwise return 0.
 *
 * This function is intended to simplify locking around refcounting for
 * objects that can be looked up from a lookup structure, and which are
 * removed from that lookup structure in the object destructor.
 * Operations on such objects require at least a read lock around
 * lookup + kref_get, and a write lock around kref_put + remove from lookup
 * structure. Furthermore, RCU implementations become extremely tricky.
 * With a lookup followed by a kref_get_unless_zero *with return value check*
 * locking in the kref_put path can be deferred to the actual removal from
 * the lookup structure and RCU lookups become trivial.
 */
static inline int __must_check kref_get_unless_zero(struct kref *kref)
{
	return atomic_add_unless(&kref->refcount, 1, 0);
}
#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(3,8,0)) */

#endif /* LINUX_3_8_COMPAT_H */
