var ConvertLib = artifacts.require("./ConvertLib.sol");
var Ticket = artifacts.require("./Ticket.sol");

module.exports = function(deployer) {
  deployer.deploy(ConvertLib);
  deployer.link(ConvertLib, Ticket);
  deployer.deploy(Ticket);
};
