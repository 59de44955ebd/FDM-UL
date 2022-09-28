# Free Download Manager Ultra-Light (FDM-UL)

A stripped-down, portable (not using the Windows Registry at all) version of [Free Download Manager Classic for Windows](https://www.freedownloadmanager.org/) with various outdated and irrelevant features removed, and therefor with small memory footprint (particularly if compared with current FDM versions based on Qt).

FDM-UL is based on the source code of [FDM 3.9.7](https://sourceforge.net/p/freedownload/code/HEAD/tree/), with about 50% of the original code removed.

**New Features**

* SOCKS5 proxy support
* Integrated minimal Web Interface

  If activated, it only provides the single endpoint "/adddownload.req?URL=[url]", where [url] can either be a single URL or a list of multiple URLs separated by linefeed (\n). Useful for adding download jobs to FDM-UL from a browser via boomarklet.

**Removed Features**

* Bittorrent support
* Browser integration based on outdated plugin interfaces (COM, NSAPI)
* Streaming protocols (Flash Video Streams/RTMP, RTSP, MMS)
* Dial-up connections/RAS
* Integration of Anti-Virus software
* "Mirrors" (looking up files at file-hosting services which were common back then)
* Site Explorer
* HTML Spider
* Floating extra windows
* Skins
* Language localisation (UI is just in english)
* Download history

**Screenshot**

![](screenshots/fdm-ul.png)
