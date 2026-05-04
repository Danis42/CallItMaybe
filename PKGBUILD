# Maintainer: Danis42 <ciammo@web.de>
pkgname=maybe
_reponame=CallItMaybe
pkgver=1.0.0
pkgrel=1
pkgdesc="Run a command by chance"
arch=('x86_64' 'aarch64')
url="https://github.com/Danis42/CallItMaybe"
license=('MIT')
source=("$pkgname-$pkgver.tar.gz::https://github.com/Danis42/$_reponame/archive/v$pkgver.tar.gz")
sha256sums=('93f912806aeab8f1c4682c83442f610870078bca74e05e60684503bc92507371')

build() {
    cd "$_reponame-$pkgver"
    make
}

package() {
    cd "$_reponame-$pkgver"
    make install DESTDIR="$pkgdir" PREFIX=/usr
}
