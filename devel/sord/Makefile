# Created by: meka
# $FreeBSD$

PORTNAME=	sord
PORTVERSION=	0.16.0
CATEGORIES=	devel
MASTER_SITES=	http://download.drobilla.net/

MAINTAINER=	meka@tilda.center
COMMENT=	C library for storing RDF data in memory

LICENSE=	ISC
LICENSE_NAME=	ISC
LICENSE_FILE=	${WRKDIR}/${PORTNAME}-${PORTVERSION}/COPYING
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

USES=		pkgconfig tar:bzip2 waf
PKG_CONFIG_PATH=	${PREFIX}/libdata/pkgconfig
CONFIGURE_ARGS+=	PKG_CONFIG_PATH=${PKG_CONFIG_PATH}

LIB_DEPENDS+=	libserd-0.so:devel/serd
LIB_DEPENDS+=	libpcre.so:devel/pcre

post-install:
	${MV} ${STAGEDIR}${PREFIX}/lib/pkgconfig ${STAGEDIR}${PREFIX}/libdata/
	${MV} ${STAGEDIR}${PREFIX}/share/man/man1 ${STAGEDIR}${PREFIX}/man/
	${RMDIR} ${STAGEDIR}${PREFIX}/share/man

.include <bsd.port.mk>
