#pragma once

#include <cstddef>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>

/// English keys and Russian translations stored in a binary search tree.
class Dictionary {
 public:
  using Entry = std::pair<std::string, std::string>;

  Dictionary();
  Dictionary(const Dictionary& other);
  Dictionary& operator=(const Dictionary& other);
  ~Dictionary();

  /// Insert a word or update its existing translation.
  Dictionary& operator+=(const Entry& entry);
  /// Insert a pair of null-terminated strings.
  Dictionary& operator+=(const std::pair<const char*, const char*>& entry);
  /// Remove a word if it exists.
  Dictionary& operator-=(const std::string& word);
  /// Find a translation, throwing std::out_of_range for an unknown word.
  const std::string& operator[](const std::string& word) const;
  /// Find a translation and allow the caller to replace it.
  std::string& operator[](const std::string& word);
  std::size_t Size() const;
  /// Replace the dictionary with entries read from a text file.
  bool LoadFile(const std::string& path);

  bool operator==(const Dictionary& other) const;
  bool operator!=(const Dictionary& other) const;

  /// Write the count followed by the entries in alphabetical order.
  friend std::ostream& operator<<(std::ostream& output, const Dictionary& data);
  /// Read a count followed by that many pairs of quoted strings.
  friend std::istream& operator>>(std::istream& input, Dictionary& data);

 private:
  struct Node {
    explicit Node(const Entry& entry) : entry(entry) {}
    Entry entry;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };

  static std::unique_ptr<Node> Copy(const std::unique_ptr<Node>& node);
  static bool Remove(std::unique_ptr<Node>& node, const std::string& word);
  static void RemoveRoot(std::unique_ptr<Node>& node);
  static std::unique_ptr<Node> TakeSmallest(std::unique_ptr<Node>& node);
  static void WriteEntries(std::ostream& output, const Node* node);
  const Node* Find(const std::string& word) const;
  bool HasSameEntries(const Node* node) const;

  std::unique_ptr<Node> root_;
  std::size_t size_ = 0;
};
