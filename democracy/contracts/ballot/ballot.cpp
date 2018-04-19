#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using namespace std;

class ballot : public contract {
    using contract::contract;

    public:
        ballot( account_name self ) :
            contract(self),
            _votes_casted(_self, _self),
            _ballots(_self, _self)
            {}

        // @abi action
        void propose( account_name sender, string proposal ){
            require_auth(sender);

            eosio_assert(proposal != "", "Proposal value cannot be empty");

            auto new_ballot_itr = _ballots.emplace( _self, [&]( auto& ballot) {
                ballot.id = _ballots.available_primary_key();
                ballot.owner = sender;
                ballot.proposal = proposal;
            });

            print((uint64_t)new_ballot_itr->id);
        }

        /**
         * Vote for a specific ballot
         */
        // @abi action
        void vote( account_name voter, uint64_t ballot_id ) {
          require_auth(voter);

          auto iter = _ballots.find(ballot_id);

          // assert basically checks if iteration is at the end, meaning there is
          // no value
          eosio_assert(iter != _ballots.end(), "Could not find ballot");


          _ballots.modify( iter, 0, [&]( auto& ballot) {
             ballot.votes.emplace_back(voter);
          });
        }

    private:

    	// @abi table
    	struct votes_casted {
    		account_name voter;
    		uint64_t times_voted;

    		account_name primary_key() const { return voter; }

    		EOSLIB_SERIALIZE( votes_casted, (voter)(times_voted))
    	};

   		multi_index<N(votes_casted), votes_casted> _votes_casted;

   		// @abi table ballots i64
   		struct ballots {
        uint64_t id;
   			account_name owner = 0;
   			string proposal;
        std::vector<account_name> votes;

        uint64_t primary_key() const { return id; }

        EOSLIB_SERIALIZE( ballots, (id)(owner)(proposal)(votes))
   		};

      multi_index<N(ballots), ballots> _ballots;

};

EOSIO_ABI( ballot, (propose)(vote) )