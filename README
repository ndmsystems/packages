NDM Systems optware feed

#Create gpl release
./gpl_release.sh -o <profile>

#Unpack tarball
tar -xvf <gpl_release.tar.gz>
mv <gpl_release> <build_dir>
cd <build_dir>
./configire.sh <profile>

#Install packets from feeds
./scripts/feeds update
./scripts/feeds list

./scripts/feeds install <packet>
#Or install all packets from feed
./scripts/feeds install -a

make menuconfig
#Mark packets (M) which should be build
make

#Prepare usb flash drive
#create ext2/3 partition

#Create "install" directory on the root of your usb flash drive
mkdir <flash>/install

#Copy mandatory packets
cd <build_dir>/bin/<platform>/packages/
#install uClibc standart library
cp libc_*.ipk           <flash>/install
cp libgcc_*.ipk         <flash>/install
cp libpthread_*.ipk     <flash>/install
cp librt_*.ipk          <flash>/install

#install busybox
cp busybox_*.ipk        <flash>/install

#install dropbear stuff
cp libndm_*.ipk         <flash>/install
cp libpam_*.ipk         <flash>/install
cp pam_ndm_*.ipk        <flash>/install
cp dropbear_*.ipk       <flash>/install

#install opkg
cp opkg_*.ipk           <flash>/install

#Copy optional packets and kernel modules
#
