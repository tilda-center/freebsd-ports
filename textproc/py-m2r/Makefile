# Created by: John W. O'Brien <john@saltant.com>
# $FreeBSD$

PORTNAME=	m2r
PORTVERSION=	0.1.5
CATEGORIES=	textproc devel python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	john@saltant.com
COMMENT=	Convert markdown formatted file with reST markup to reST format

LICENSE=	MIT

TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}coverage>0:devel/py-coverage \
		${PYTHON_PKGNAMEPREFIX}sphinx>0:textproc/py-sphinx
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}mistune>0:textproc/py-mistune \
		${PYTHON_PKGNAMEPREFIX}docutils>0:textproc/py-docutils

USES=		python
USE_PYTHON=	autoplist concurrent distutils

NO_ARCH=	yes

.include <bsd.port.pre.mk>

.if ${PYTHON_REL} < 3300
TEST_DEPENDS+=	${PYTHON_PKGNAMEPREFIX}mock>0:devel/py-mock
.endif

do-test:
	@cd ${TEST_WRKSRC} && ${PYTHON_CMD} ${PYDISTUTILS_SETUP} test

.include <bsd.port.post.mk>
