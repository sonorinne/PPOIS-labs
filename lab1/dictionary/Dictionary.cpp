#include "Dictionary.h"

#include <fstream>
#include <iomanip>
#include <stdexcept>

Dictionary::Dictionary() = default;
Dictionary::~Dictionary() = default;

Dictionary::Dictionary(const Dictionary& other)
    : root_(Copy(other.root_)), size_(other.size_) {}

Dictionary& Dictionary::operator=(const Dictionary& other) {
  if (this != &other) {
    root_ = Copy(other.root_);
    size_ = other.size_;
  }
  return *this;
}

std::unique_ptr<Dictionary::Node> Dictionary::Copy(
    const std::unique_ptr<Node>& node) {
  if (!node) return nullptr;
  auto copy = std::make_unique<Node>(node->entry);
  copy->left = Copy(node->left);
  copy->right = Copy(node->right);
  return copy;
}

Dictionary& Dictionary::operator+=(const Entry& entry) {
  auto* link = &root_;
  while (*link) {
    Node& node = **link;
    if (entry.first == node.entry.first) {
      node.entry.second = entry.second;
      return *this;
    }
    link = entry.first < node.entry.first ? &node.left : &node.right;
  }
  *link = std::make_unique<Node>(entry);
  ++size_;
  return *this;
}

Dictionary& Dictionary::operator+=(
    const std::pair<const char*, const char*>& entry) {
  return *this += Entry{entry.first, entry.second};
}

Dictionary& Dictionary::operator+=(const std::pair<char*, char*>& entry) {
  return *this += Entry{entry.first, entry.second};
}

Dictionary& Dictionary::operator-=(const std::string& word) {
  if (Remove(root_, word)) --size_;
  return *this;
}

bool Dictionary::Remove(std::unique_ptr<Node>& node, const std::string& word) {
  if (!node) return false;
  if (word < node->entry.first) return Remove(node->left, word);
  if (word > node->entry.first) return Remove(node->right, word);
  RemoveRoot(node);
  return true;
}

void Dictionary::RemoveRoot(std::unique_ptr<Node>& node) {
  auto old = std::move(node);
  if (!old->left) {
    node = std::move(old->right);
  } else if (!old->right) {
    node = std::move(old->left);
  } else {
    node = TakeSmallest(old->right);
    node->left = std::move(old->left);
    node->right = std::move(old->right);
  }
}

std::unique_ptr<Dictionary::Node> Dictionary::TakeSmallest(
    std::unique_ptr<Node>& node) {
  if (node->left) return TakeSmallest(node->left);
  auto smallest = std::move(node);
  node = std::move(smallest->right);
  return smallest;
}

const Dictionary::Node* Dictionary::Find(const std::string& word) const {
  const Node* node = root_.get();
  while (node && node->entry.first != word) {
    node = word < node->entry.first ? node->left.get() : node->right.get();
  }
  return node;
}

const std::string& Dictionary::operator[](const std::string& word) const {
  const Node* node = Find(word);
  if (!node) throw std::out_of_range("Unknown word: " + word);
  return node->entry.second;
}

std::string& Dictionary::operator[](const std::string& word) {
  return const_cast<std::string&>(std::as_const(*this)[word]);
}

std::size_t Dictionary::Size() const { return size_; }

bool Dictionary::LoadFile(const std::string& path) {
  std::ifstream input(path);
  return static_cast<bool>(input >> *this);
}

bool Dictionary::HasSameEntries(const Node* node) const {
  if (!node) return true;
  const Node* match = Find(node->entry.first);
  return match && match->entry.second == node->entry.second &&
         HasSameEntries(node->left.get()) && HasSameEntries(node->right.get());
}

bool Dictionary::operator==(const Dictionary& other) const {
  return size_ == other.size_ && HasSameEntries(other.root_.get());
}

bool Dictionary::operator!=(const Dictionary& other) const {
  return !(*this == other);
}

void Dictionary::WriteEntries(std::ostream& output, const Node* node) {
  if (!node) return;
  WriteEntries(output, node->left.get());
  output << std::quoted(node->entry.first) << ' '
         << std::quoted(node->entry.second) << '\n';
  WriteEntries(output, node->right.get());
}

std::ostream& operator<<(std::ostream& output, const Dictionary& data) {
  output << data.size_ << '\n';
  Dictionary::WriteEntries(output, data.root_.get());
  return output;
}

std::istream& operator>>(std::istream& input, Dictionary& data) {
  int count = 0;
  if (!(input >> count)) return input;
  if (count < 0) {
    input.setstate(std::ios::failbit);
    return input;
  }
  Dictionary loaded;
  for (int index = 0; index < count; ++index) {
    Dictionary::Entry entry;
    if (!(input >> std::quoted(entry.first) >> std::quoted(entry.second))) {
      return input;
    }
    loaded += entry;
  }
  data.root_ = std::move(loaded.root_);
  data.size_ = loaded.size_;
  return input;
}
