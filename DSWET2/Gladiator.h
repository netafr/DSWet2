
#ifndef GLADIATOR_H
#define GLADIATOR_H

/*
 This class represents a Gladiator.
 A gladiator have id (unique identifier) and score.

 */
class Gladiator {
    int id;
    int score;

public:
    /* Description:  Cto'r
   * Input:         id - the gladiator's id - unique identifier
                    score - the gladiator's score
   * Return Values: None.
   */
    Gladiator(int id, int score) : id(id), score(score) {}
    /* Description:  copy Cto'r
    * Input:		 glad, reference to the gladiator being copied.
    */
    Gladiator(const Gladiator& glad) {
        id = glad.id;
        score = glad.score;
    }
 /* Description:   (Equal to operator)Compares between two gladiators.
                   Two gladiators are euqal if their id (unique) is same.
  * Input:         glad - Reference to gladiator to compare with.
  * Output:        None.
  * Return Values: True if gladiators are equal, else False.
  */
    bool operator==(const Gladiator& glad) const {
        return id == glad.id;
    }
    /* Description:  (Less than operator) Checks whether (this)gladiator is smaller than given one.
	 				 The one with smaller score is smaller. If both have same score, the
					 one with bigger ID is smaller.
	* Input:         Reference to gladiator to compare with.
	* Output:        None.
	* Return Values: True if (this)gladiator is smaller, else False.
	*/
    bool operator<(const Gladiator& glad) const {
        if (score == glad.score)
            return id > glad.id;
        return score < glad.score;
    }
    /* Description:  (Greater than operator) Checks whether (this)gladiator is Bigger than given one.
	* Input:         Reference to gladiator to compare with.
	* Output:        None.
	* Return Values: True if (this)gladiator is bigger, else False.
	*/
    bool operator>(const Gladiator& glad) const {
        return glad <(*this);
    }
    /* Description:  Dto'r.
    */
    ~Gladiator() {}
};


#endif //GLADIATOR_H
