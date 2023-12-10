**Personal PKGBUILDs**

If you’d rather only checkout one folder instead of clone the entire repo:

```
git clone -n --depth=1 --filter=tree:0 https://github.com/yochananmarqos/pkgbuilds
cd pkgbuilds
git sparse-checkout set --no-cone <folder-name>
git checkout
```

Also see my [PKGBUILDs](https://aur.archlinux.org/packages/?O=0&SeB=M&K=yochananmarqos&outdated=&SB=n&SO=a&PP=50&do_Search=Go) in the Arch User Repository (AUR)