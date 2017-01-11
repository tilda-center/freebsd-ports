# Created by: Goran Mekić <meka@tilda.center>
# $FreeBSD$

PORTNAME=	zita-resampler
PORTVERSION=	1.6.0
CATEGORIES=	audio
MASTER_SITES=	http://kokkinizita.linuxaudio.org/linuxaudio/downloads/
WRKSRC_SUBDIR=	libs

MAINTAINER=	meka@tilda.center
COMMENT=	C++ library for resampling audio signals.

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		tar:bzip2 gmake

MY_WORKDIR=	${WRKDIR}/${PORTNAME}-${PORTVERSION}

post-extract:
	ln -s ${MY_WORKDIR}/COPYING ${MY_WORKDIR}/${WRKSRC_SUBDIR}/COPYING

post-install:
	${MV} ${STAGEDIR}${PREFIX}/libamd64/* ${STAGEDIR}${PREFIX}/lib/
	${RMDIR} ${STAGEDIR}${PREFIX}/libamd64

.include <bsd.port.mk>
