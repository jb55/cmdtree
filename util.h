
/* See LICENSE file for copyright and license details. */

#ifndef CMDTREE_UTIL_H
#define CMDTREE_UTIL_H

#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))

#define INTERSECT(x,y,w,h,r)  (MAX(0, MIN((x)+(w),(r).x_org+(r).width)  - MAX((x),(r).x_org)) \
			       * MAX(0, MIN((y)+(h),(r).y_org+(r).height) - MAX((y),(r).y_org)))
#define LENGTH(X)             (sizeof X / sizeof X[0])
#define TEXTW(X)              (drw_fontset_getwidth(drw, (X)) + lrpad)

#define UTF_INVALID 0xFFFD
#define UTF_SIZ     4


void die(const char *fmt, ...);
void *ecalloc(size_t nmemb, size_t size);

long utf8decodebyte(const char c, size_t *i);
size_t utf8validate(long *u, size_t i);
size_t utf8decode(const char *c, long *u, size_t clen);

#endif /* CMDTREE_UTIL_H */
