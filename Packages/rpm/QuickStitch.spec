Name:           QuickStitch
Version:        1.1.0
Release:        1%{?dist}
Summary:        Simple image stitching program written in Qt5 C++.

License:        GPLv3
URL:            https://vivx701.github.io/QuickStitch
Source0:        https://github.com/Vivx701/QuickStitch/archive/1.1.0.tar.gz

BuildRequires:  desktop-file-utils
BuildRequires:  gcc-c++
BuildRequires:  qt5-qtbase-devel
BuildRequires:  qt5-qtsvg-devel
BuildRequires:  qt5-qttools-devel
BuildRequires:  qt5-qtx11extras-devel

Requires:       hicolor-icon-theme      

%description
Simple image stitching program written in Qt5 C++.
Provides functionalites to stitch images horizonally and vertically.


%prep
%autosetup



%build
mkdir %{_target_platform}
pushd %{_target_platform}
%{qmake_qt5} ..
%make_build
popd


%install
rm -rf $RPM_BUILD_ROOT
make install INSTALL_ROOT=%{buildroot} -C %{_target_platform}


%files
%license COPYING
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/scalable/apps/%{name}.svg



%changelog
* Mon Apr 22 2019 Vivek.P <vivx_developer@yahoo.in>
- initial package for fedora %{name}-%{version}

