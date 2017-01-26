# Created by: Goran Mekić <meka@tilda.center>
# $FreeBSD$

PORTNAME=	eq10q
PORTVERSION=	2.2
CATEGORIES=	audio
MASTER_SITES=	SF/${PORTNAME}

MAINTAINER=	meka@tilda.center
COMMENT=	Set of mono and stereo parametric equalizers

LICENSE=	GPLv2+

BUILD_DEPENDS=	lv2>=1.14.0:audio/lv2\
		pkg-config:devel/pkgconf
LIB_DEPENDS= libjack.so:audio/jack \
		libgtkmm-2.4.so:x11-toolkits/gtkmm24 \
		libfftw3.so:math/fftw3

USES=		cmake

LDFLAGS+=	-L${LOCALBASE}/lib

.include <bsd.port.mk>
