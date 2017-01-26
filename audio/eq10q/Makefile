# Created by: Goran Mekić <meka@tilda.center>
# $FreeBSD$

PORTNAME=	eq10q
PORTVERSION=	2.2
CATEGORIES=	audio
MASTER_SITES=	SF/${PORTNAME}

MAINTAINER=	meka@tilda.center
COMMENT=	Set of mono and stereo parametric equalizers

LICENSE=	GPLv2+

BUILD_DEPENDS=	lv2>=1.14.0:audio/lv2
LIB_DEPENDS= libjack.so:audio/jack

USES=		cmake

LDFLAGS=	-L/usr/local/lib

.include <bsd.port.mk>
