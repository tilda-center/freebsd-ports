# Created by: Goran Mekić <meka@tilda.center>
# $FreeBSD$

PORTNAME=	drumgizmo
PORTVERSION=	0.9.13
CATEGORIES=	audio
MASTER_SITES=	http://www.drumgizmo.org/releases/${PORTNAME}-${PORTVERSION}/

MAINTAINER=	meka@tilda.center
COMMENT=	Multichannel drum sampler

LICENSE=	LGPL3+

BUILD_DEPENDS=	lv2>=1.14.0:audio/lv2 \
		pkg-config:devel/pkgconf
LIB_DEPENDS=	libsmf.so:audio/libsmf \
		libzita-resampler.so:audio/zita-resampler \
		libjack.so:audio/jack \
		libsndfile.so:audio/libsndfile \
		libexpat.so:textproc/expat2

HAS_CONFIGURE=	YES
USES=		gettext-runtime libtool
USE_GNOME=	glib20
USE_XORG=	x11

CPPFLAGS+=	-I../include -I../../include -I../src -I../../src
EXPAT_CFLAGS=	-I${LOCALBASE}/include
EXPAT_LDFLAGS=	-L${LOCALBASE}/lib
ZITA_CPPFLAGS=	-I${LOCALBASE}/include
ZITA_LDFLAGS=	-L${LOCALBASE}/lib

CONFIGURE_ENV+= EXPAT_CFLAGS=${EXPAT_CFLAGS} EXPAT_LDFLAGS=${EXPAT_LDFLAGS}
CONFIGURE_ENV+=	ZITA_CPPFLAGS=${ZITA_CPPFLAGS} ZITA_LDFLAGS=${ZITA_LDFLAGS}
CONFIGURE_ARGS=	--disable-output-alsa --enable-lv2

.include <bsd.port.mk>
