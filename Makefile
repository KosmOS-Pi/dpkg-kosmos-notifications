PREFIX ?= /usr
BINDIR = $(PREFIX)/bin
AUTOSTARTDIR = /etc/xdg/autostart
SCRIPT = kosmos-notifications
DESKTOP = kosmos-notifications.desktop

INSTALL = install
INSTALL_DIR = $(INSTALL) -d
INSTALL_BIN = $(INSTALL) -m 755
INSTALL_DATA = $(INSTALL) -m 644

all:
	@echo "Use 'make install' to install or 'make uninstall' to remove."

install:
	@echo "Installing $(SCRIPT) to $(DESTDIR)$(BINDIR)..."
	$(INSTALL_DIR) $(DESTDIR)$(BINDIR)
	$(INSTALL_BIN) $(SCRIPT) $(DESTDIR)$(BINDIR)/$(SCRIPT)
	@echo "Installing autostart file to $(DESTDIR)$(AUTOSTARTDIR)..."
	$(INSTALL_DIR) $(DESTDIR)$(AUTOSTARTDIR)
	$(INSTALL_DATA) $(DESKTOP) $(DESTDIR)$(AUTOSTARTDIR)/$(DESKTOP)
	@echo "Installation complete."

uninstall:
	@echo "Removing installed files..."
	rm -f $(DESTDIR)$(BINDIR)/$(SCRIPT)
	rm -f $(DESTDIR)$(AUTOSTARTDIR)/$(DESKTOP)
	@echo "Uninstallation complete."

clean:
	@echo "Cleaning..."
	rm -rf debian/tmp debian/.debhelper debian/*substvars debian/files || true
	find . -name '__pycache__' -type d -exec rm -rf {} + || true
	@echo "Clean complete."

.PHONY: all install uninstall clean
