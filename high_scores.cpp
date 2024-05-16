#include "include/high_scores.h"
#include "include/global_instances.h"
#include "include/types.h"
#include <string>

int calculate_high_score_position() {
    // Iterate through the high scores to find the position for the current score
    for (int i = 0; i < 10; i++) {
        if (json_read_number_as_int(game_data.score_rows[i], "score") < game_data.score) {
            return i;
        }
    }
    return 10;
}

void update_high_scores() {
    int position = calculate_high_score_position();

    // Shift the scores below the current position down by one position
    for (int i = 9; i > position; i--) {
        const string previous_initials = json_read_string(game_data.score_rows[i - 1], "initials");
        const int previous_score = json_read_number_as_int(game_data.score_rows[i - 1], "score");
        json_set_number(game_data.score_rows[i], "score", previous_score);
        json_set_string(game_data.score_rows[i], "initials", previous_initials);
    }

    // Insert the current score and initials at the calculated position
    json_set_number(game_data.score_rows[position], "score", game_data.score);
    std::string initials = initials_entry.characters[initials_entry.character_1] + initials_entry.characters[initials_entry.character_2];
    json_set_string(game_data.score_rows[position], "initials", initials);

    // Update the scores JSON object with the modified score rows
    for (int i = 0; i < 10; i++) {
        json_set_object(game_data.scores, "row" + std::to_string(i), game_data.score_rows[i]);
    }

    // Save the updated scores to the JSON file
    json_to_file(game_data.scores, "scores.json");
}
