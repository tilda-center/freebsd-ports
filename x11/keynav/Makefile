# $FreeBSD$

PORTNAME=	keynav
DISTVERSION=	0.20110708.0
PORTREVISION=	2
PORTEPOCH=	1
CATEGORIES=	x11
MASTER_SITES=	http://semicomplete.googlecode.com/files/

MAINTAINER=	wxs@FreeBSD.org
COMMENT=	Quickly select a portion of the screen using minimal keystrokes

BROKEN=		Unfetchable (google code has gone away)
DEPRECATED=	Unfetchable for more than six months (google code has gone away)
EXPIRATION_DATE=	2017-04-30
BROKEN_aarch64=	Fails to build: undefined reference to xdo_mouselocation

LIB_DEPENDS=	libxdo.so:x11/xdotool \
		libcairo.so:graphics/cairo

USES=		gmake pkgconfig
USE_GNOME=	glib20
USE_XORG=	xtst x11 xinerama

PLIST_FILES=	bin/keynav
PORTEXAMPLES=	keynavrc

OPTIONS_DEFINE=	EXAMPLES

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/keynav ${STAGEDIR}${PREFIX}/bin
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/keynavrc ${STAGEDIR}${EXAMPLESDIR}

.include <bsd.port.mk>
