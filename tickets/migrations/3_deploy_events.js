var Event = artifacts.require("./Event.sol");

module.exports = function(deployer) {
  deployer.deploy(Event, "Dekmantel", 100);
};
