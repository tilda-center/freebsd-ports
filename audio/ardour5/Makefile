# Created by: Goran Mekić <meka@tilda.center>
# $FreeBSD$

PORTNAME=	ardour5
PORTVERSION=	5.5.0
CATEGORIES=	audio
MASTER_SITES=	https://community.ardour.org/
DISTNAME=	srctar
EXTRACT_SUFX=

MAINTAINER=	meka@tilda.center
COMMENT=	Multichannel digital audio and MIDI workstation

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

RUN_DEPENDS=	lv2specgen.py:audio/lv2

LIB_DEPENDS=	liblo.so:audio/liblo \
		libjack.so:audio/jack \
		libaubio.so:audio/aubio \
		liblrdf.so:textproc/liblrdf \
		libglib-2.0.so:devel/glib20 \
		libglibmm-2.4.so:devel/glibmm \
		libarchive.so.13:archivers/libarchive \
		libtag.so:audio/taglib \
		libvamp-sdk.so:audio/vamp-plugin-sdk \
		librubberband.so:audio/rubberband \
		libpangomm-1.4.so:x11-toolkits/pangomm \
		libserd-0.so:devel/serd \
		libsord-0.so:devel/sord \
		libsratom-0.so:audio/sratom \
		liblilv-0.so:audio/lilv \
		libgtkmm-2.4.so:x11-toolkits/gtkmm24 \
		libboost_date_time.so:devel/boost-libs

USES=		cpe gettext waf pkgconfig tar:bzip2
CONFIGURE_TARGET=	configure --boost-include=${LOCALBASE}/include

BROKEN_powerpc64=	Does not build

WRKSRC=		${WRKDIR}/Ardour-${PORTVERSION}

.include <bsd.port.mk>
