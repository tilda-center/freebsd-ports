# Created by: Sokolov Alexey <sokolov@TrueBSD.org>
# $FreeBSD$

PORTNAME=	qwit
DISTVERSION=	r154
PORTREVISION=	3
CATEGORIES=	net-im
MASTER_SITES=	GOOGLE_CODE
DISTNAME=	qwit-${PORTVERSION}-src

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Qt4-based lightweight Twitter client

BROKEN=		Unfetchable (google code has gone away)
DEPRECATED=	Unfetchable for more than six months (google code has gone away)
EXPIRATION_DATE=	2017-04-30

USES=		qmake tar:bzip2
USE_QT4=	gui network xml moc_build rcc_build \
		uic_build
post-patch:
	${REINPLACE_CMD} '/icon.path/s,share/icons,share/pixmaps,' \
		${WRKSRC}/qwit.pro

.include <bsd.port.mk>
