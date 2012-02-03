## Readme document for QtDockTime library

Using issue of docks on desktops today become more and more popular. There is at least 3 popular solutions of this issue: MacOS Dock, Windows 7 taskbar and Unity launchers from Ubuntu. Also there is icon tasks in KDE 4.8.
Looking at this, there is a need to cross-platform library for the work with all this docks.

### Common issues for docks

* Badges
* Progress indicator
* Menu
* Alarms

All this things are basics and they are fully supported in Win7, MacOS and Ubuntu. On this basis QtDockTile API will be built and all platform-dependent extensions will be added by the time of development and they won't be essentials.

### Architecture of library and using in your code

For maximum flexibility and extensibility realization in every is usual Qt plugins. It allows adding support of new API without recompiling all the library, and in the case of inability of using any realization, plugin just won't work. The plugins are booted by the special singleton-manager. Every plugin inform this manager if it can work in this enviroment or not, resulting in thing that manager can call methods in only that plugins, which are allowed in this enviroment.
User just work with simle class QtDockTile that is front-end to this manager. So you can create any number of QtDockTile instance.
For the realization of dock menu Qt QMenu will be used. It is important to know about restrictions on the platform, which you use.

Simple example in code:<br />
<code>
<br />
m_tile = new QtDockTile(this); <br />
m_tile->setMenu(ui->menu);<br />
connect(ui->pushButton, SIGNAL(clicked()), m_tile, SLOT(alert()));<br />
m_tile->setBadge(123); <br />
connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), m_tile, SLOT(setProgress(int)));
<br />
</code>

As you can see, it is very simple!

### Restrictions
