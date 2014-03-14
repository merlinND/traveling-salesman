VAGRANTFILE_API_VERSION = "2"

$script = <<SCRIPT
sudo yum install ncurses-devel tcl-devel gcc-c++
SCRIPT

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "fedora18_x64_nocm"
  config.vm.box_url = "http://puppet-vagrant-boxes.puppetlabs.com/fedora-18-x64-vbox4210-nocm.box"
  config.vm.provision "shell", inline: $script
end
