# Created by: meka
# $FreeBSD$

PORTNAME=	lilv
PORTVERSION=	0.24.0
CATEGORIES=	audio
MASTER_SITES=	http://download.drobilla.net/

MAINTAINER=	meka@tilda.center
COMMENT=	C library to make the use of LV2 plugins as simple as possible

LICENSE=	ISC
LICENSE_NAME=	ISC
LICENSE_FILE=	${WRKDIR}/${PORTNAME}-${PORTVERSION}/COPYING
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

USES=		pkgconfig tar:bzip2 waf
PKG_CONFIG_PATH=	${PREFIX}/libdata/pkgconfig
CONFIGURE_ARGS+=	PKG_CONFIG_PATH=${PKG_CONFIG_PATH}

LIB_DEPENDS+=	libserd-0.so:devel/serd
LIB_DEPENDS+=	libsord-0.so:devel/sord
LIB_DEPENDS+=	libsratom-0.so:audio/sratom
LIB_DEPENDS+=	libsndfile.so:audio/libsndfile
RUN_DEPENDS+=	lv2specgen.py:audio/lv2
BUILD_DEPENDS+=	lv2specgen.py:audio/lv2

post-install:
	${MV} ${STAGEDIR}${PREFIX}/lib/pkgconfig ${STAGEDIR}${PREFIX}/libdata/
	${MV} ${STAGEDIR}${PREFIX}/share/man/man1 ${STAGEDIR}${PREFIX}/man/
	${RMDIR} ${STAGEDIR}${PREFIX}/share/man

.include <bsd.port.mk>
