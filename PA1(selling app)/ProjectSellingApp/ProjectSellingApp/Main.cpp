#include "Account/Bucket/Bucket.h"

int main() {
    Bucket b("quythanh");
    // Bucket b2("customer");
    b.PrintAll();
    b.Add();
    b.Remove();
    b.PrintAll();
}
