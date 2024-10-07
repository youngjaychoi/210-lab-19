#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

struct Review {
    double rating;
    string comment;
    Review *next;
};

class Movie {
private:
    string title;
    Review *head;

    Review* createReview(double rating, string &comment);
    void addReview(double rating, string &comment);

public:
    Movie(string movieTitle) : title(movieTitle), head(nullptr) {}
    void readFile(const string &inFile);
    void outputReview() const;
};

int main() {
    srand(time(0));

    vector<Movie> movies = {
        Movie("Movie 1"),
        Movie("Movie 2"),
        Movie("Movie 3"),
        Movie("Movie 4")
    };

    string inFile = "C:/code/comments.txt";
    for (auto &movie : movies) {
        movie.readFile(inFile);
    }

    for (const auto &movie : movies) {
        movie.outputReview();
        cout << endl;
    }

    return 0;
}

Review* Movie::createReview(double rating, string &comment) {
        Review *newReview = new Review;
        newReview->rating = rating;
        newReview->comment = comment;
        newReview->next = nullptr;
        return newReview;
    }

void Movie::addReview(double rating, string &comment) {
    Review *newReview = createReview(rating, comment);

    if (!head) {
        head = newReview;
    } else {
        newReview->next = head;
        head = newReview;
    }
}

void Movie::readFile(const string &inFile) {
        ifstream file(inFile);
        string comment;


        if (!file.is_open()) {
            cout << "Error! file not opened" << endl;
            return;
        }

        while (getline(file, comment)) {
            double rating = 1.0 + static_cast<double>(rand())
                / (static_cast<double>(RAND_MAX / 4.0));
            rating = round(rating * 10) / 10.0;
            
            addReview(rating, comment);
        }
        
        file.close();
    }

void Movie::outputReview() const {
    if (!head) {
        cout << "No reviews for [" << title << "]." << endl;
        return;
    }

    cout << "Reviews for [" << title << "]:" << endl;

    Review *temp = head;
    int count = 0;
    double totalRating = 0.0, average = 0;

    cout << fixed << setprecision(1);
    while (temp) {
        cout << string(4, ' ') << "Review #" << (count + 1) << ": "
            << temp->rating << " - " << temp->comment << endl;
        totalRating += temp->rating;
        temp = temp->next;
        count++;
    }

    if (count > 0) {
        average = totalRating / count;
    } else {
        average = 0.0;
    }
    cout << string(4, ' ') << "Average Rating: " << average << endl;
}
