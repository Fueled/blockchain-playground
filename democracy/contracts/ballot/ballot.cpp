#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using namespace std;

class ballot : public contract {
  using contract::contract;

  public:
      ballot( account_name self ) :
        contract(self),
        members(_self, _self),
        proposals(_self, _self)
        {}

      // @abi action
      void propose( account_name sender, string description ){
        require_auth(sender);

        eosio_assert(description != "", "Proposal description cannot be empty");

        auto new_proposal = proposals.emplace( _self, [&]( auto& proposal) {
            proposal.id = proposals.available_primary_key();
            proposal.owner = sender;
            proposal.description = description;
        });

        print((uint64_t)new_proposal->id);
      }

      /**
       * Vote for a specific ballot
       */
      // @abi action
      void vote( account_name account, uint64_t proposal_id ) {

        require_auth(account);
        auto member = retrieve_member(account);

        auto iter = proposals.find(proposal_id);

        // assert basically checks if iteration is at the end, meaning there is
        // no value
        eosio_assert(iter != proposals.end(), "Could not find proposal");

        proposals.modify( iter, 0, [&]( auto& proposal) {

          // Check if the member already casted a vote
          for(auto const& value: proposal.votes) {
            eosio_assert(value.owner != member.owner, "Member already voted");
          }

          proposal.votes.emplace_back();
          proposal.votes.back().owner = member.owner;
          proposal.votes.back().weight = member.weight;
        });
      }

      // @abi action
      void add_member( account_name issue, account_name account ) {
        auto iter = members.find(voter);
        eosio_assert(iter == members.end(), "Account is already member of democracy");
      }

    private:

    	// @abi table member i64
    	struct Member {
    		account_name owner;
    		uint64_t weight;
        account_name granter;

    		account_name primary_key() const { return owner; }

    		EOSLIB_SERIALIZE( Member, (owner)(weight))
    	};

      /**
       * Requires the account to be a member, returns the member struct
       */
      Member retrieve_member( account_name voter) {
        auto iter = members.find(voter);
        eosio_assert(iter != members.end(), "Account is not a member of this democracy");

        return *iter;
      }

      struct Ballot {
          account_name owner;
          uint32_t weight;
      };

   		// @abi table proposal i64
   		struct Proposal {
        uint64_t id;
   			account_name owner = 0;
   			string description;
        std::vector<Ballot> votes;

        uint64_t primary_key() const { return id; }

        EOSLIB_SERIALIZE( Proposal, (id)(owner)(description)(votes))
   		};


      multi_index<N(Proposal), Proposal> proposals;
      multi_index<N(Member), Member> members;
};

EOSIO_ABI( ballot, (propose)(vote) )
