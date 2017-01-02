# Created by: meka
# $FreeBSD$

PORTNAME=	suil
PORTVERSION=	0.8.2
CATEGORIES=	audio
MASTER_SITES=	http://download.drobilla.net/

MAINTAINER=	meka@tilda.center
COMMENT= Lightweight C library for loading and wrapping LV2 plugin UIs

LICENSE=	ISC
LICENSE_NAME=	ISC
LICENSE_FILE=	${WRKDIR}/${PORTNAME}-${PORTVERSION}/COPYING
LICENSE_PERMS=	dist-mirror dist-sell pkg-mirror pkg-sell auto-accept

USES=		pkgconfig tar:bzip2 waf

RUN_DEPENDS+=	lv2specgen.py:audio/lv2
BUILD_DEPENDS+=	lv2specgen.py:audio/lv2

post-install:
	${MV} ${STAGEDIR}${PREFIX}/lib/pkgconfig ${STAGEDIR}${PREFIX}/libdata/

.include <bsd.port.mk>
