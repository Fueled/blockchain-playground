var Event = artifacts.require("./Event.sol");
var Ownable = artifacts.require('./Ownable.sol')
var Venue = artifacts.require("./Venue.sol");

module.exports = function(deployer) {
  deployer.deploy(Ownable);
  deployer.link(Ownable, Event);
  deployer.deploy(Venue)
};
