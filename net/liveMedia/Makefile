# Created by: nork@FreeBSD.org
# $FreeBSD$

PORTNAME=	liveMedia
PORTVERSION=	2017.01.26
PORTEPOCH=	2
CATEGORIES=	net devel
MASTER_SITES=	http://www.live555.com/liveMedia/public/ \
		https://download.videolan.org/contrib/live555/
DISTNAME=	live.${PORTVERSION}

MAINTAINER=	multimedia@FreeBSD.org
COMMENT=	LIVE.COM Streaming Media

LICENSE=	LGPL21

NO_CDROM=	'dated material'

WRKSRC=		${WRKDIR}/live

HAS_CONFIGURE=	yes

CONFIGURE_SCRIPT=	genMakefiles
CONFIGURE_ARGS=		fixed-freebsd

USES=		gmake
USE_LDCONFIG=	yes

.include <bsd.port.pre.mk>

.if ${ARCH} == "amd64" || ${ARCH} == "ia64"
CFLAGS+=	-fPIC
.else
CFLAGS+=	-fpic
.endif

.if ${ARCH} == "sparc64"
BROKEN=		Does not compile
.endif

post-extract:
	${CP} ${FILESDIR}/config.fixed-freebsd ${WRKSRC}

.if ${PREFIX} != "/usr/local"
post-configure:
	${REINPLACE_CMD} -e 's,^PREFIX = /usr/local,PREFIX = "${PREFIX}",' \
		${WRKSRC}/Makefile ${WRKSRC}/*/Makefile
.endif

.include <bsd.port.post.mk>
