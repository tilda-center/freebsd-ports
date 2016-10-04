# Created by: meka
# $FreeBSD$

PORTNAME=	lv2
PORTVERSION=	1.14.0
CATEGORIES=	devel
MASTER_SITES=	http://lv2plug.in/spec/

MAINTAINER=	meka@tilda.center
COMMENT=	C library for serialising LV2 atoms to and from RDF

LICENSE=	ISC
LICENSE_NAME=	ISC
LICENSE_FILE=	${WRKDIR}/${PORTNAME}-${PORTVERSION}/COPYING
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

USES=		pkgconfig tar:bzip2 waf
PKG_CONFIG_PATH=	${PREFIX}/libdata/pkgconfig
CONFIGURE_ARGS+=	PKG_CONFIG_PATH=${PKG_CONFIG_PATH}

CONFLICTS=	lv2core-[0-9]*

# LIB_DEPENDS+=	libserd-0.so:devel/serd
# LIB_DEPENDS+=	libpcre.so:devel/pcre

post-install:
	${MV} ${STAGEDIR}${PREFIX}/lib/pkgconfig ${STAGEDIR}${PREFIX}/libdata/

.include <bsd.port.mk>
