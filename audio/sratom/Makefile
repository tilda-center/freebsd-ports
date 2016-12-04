# Created by: meka
# $FreeBSD$

PORTNAME=	sratom
PORTVERSION=	0.6.0
CATEGORIES=	audio
MASTER_SITES=	http://download.drobilla.net/

MAINTAINER=	meka@tilda.center
COMMENT=	C library for serialising LV2 atoms to and from RDF

LICENSE=	ISC
LICENSE_NAME=	ISC
LICENSE_FILE=	${WRKDIR}/${PORTNAME}-${PORTVERSION}/COPYING
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

USES=		pkgconfig tar:bzip2 waf
PKG_CONFIG_PATH=	${PREFIX}/libdata/pkgconfig
CONFIGURE_ARGS+=	PKG_CONFIG_PATH=${PKG_CONFIG_PATH}

RUN_DEPENDS+=	lv2specgen.py:audio/lv2
BUILD_DEPENDS+=	lv2specgen.py:audio/lv2
LIB_DEPENDS+=	libserd-0.so:devel/serd
LIB_DEPENDS+=	libsord-0.so:devel/sord

post-install:
	${MV} ${STAGEDIR}${PREFIX}/lib/pkgconfig ${STAGEDIR}${PREFIX}/libdata/

.include <bsd.port.mk>
