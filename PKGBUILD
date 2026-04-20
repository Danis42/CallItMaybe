# Maintainer: Danis42 <ciammo@web.de>
pkgname=maybe
pkgver=1.0.0
pkgrel=1
pkgdesc="Run a command with 50/50 probability"
arch=('x86_64' 'aarch64')
url="https://github.com/Danis42/CallItMaybe"
license=('MIT')
source=("$pkgname-$pkgver.tar.gz::https://github.com/Danis42/CallItMaybe/archive/v$pkgver.tar.gz")
sha256sums=('SKIP')

build() {
    cd "$pkgname-$pkgver"
    make
}

package() {
    cd "$pkgname-$pkgver"
    make install DESTDIR="$pkgdir" PREFIX=/usr
}
