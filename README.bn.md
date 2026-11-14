<p align="right"><a href="README.md"><b>Read in English</b></a></p>

<p align="center">
  <img src="data/128.png" alt="খোলাবাংলা কিবোর্ড লোগো" width="128">
</p>

<h1 align="center">খোলাবাংলা কিবোর্ড</h1>

<h3 align="center">লিনাক্সে বাংলা লিখুন, ঠিক যেভাবে অভ্রতে লেখেন। ইনস্টল হয় একটি মাত্র কমান্ডে।</h3>

**খোলাবাংলা কিবোর্ড** লিনাক্সের জন্য একটি ফ্রি ও ওপেন সোর্স বাংলা ইনপুট মেথড। এতে আছে ডিকশনারি সাজেশন ও
অটোকারেক্টসহ **অভ্র ফোনেটিক**, জনপ্রিয় ফিক্সড লেআউটগুলো (প্রভাত, মুনীর অপটিমা, জাতীয়, বর্ণনা, অভ্র ইজি, খিপ্রো)
এবং টাইপিং অটোমেশন সুবিধা। এটি **IBus** ও **Fcitx5** দুটোতেই কাজ করে।

## ইনস্টল

টার্মিনাল খুলুন, নিচের **একটি মাত্র কমান্ড** পেস্ট করুন এবং <kbd>Enter</kbd> চাপুন:

```bash
bash -c "$(curl -fsSL https://raw.githubusercontent.com/tasin-py/KholaBangla/main/tools/install.sh 2>/dev/null || wget -qO- https://raw.githubusercontent.com/tasin-py/KholaBangla/main/tools/install.sh)"
```

ইনস্টলারটি নিজে থেকেই আপনার ডিস্ট্রো, ভার্সন ও প্রসেসর শনাক্ত করবে, সঠিক প্যাকেজ ইনস্টল করবে এবং
আপনার ডেস্কটপের জন্য উপযুক্ত ইনপুট মেথড (IBus বা Fcitx5) সেটআপ করে দেবে। আপনি আগে থেকে অন্য কোনো
ইনপুট মেথড ব্যবহার করলে সেটি বদলাবে না। কাজ শেষ হলে একবার লগ আউট করে আবার লগ ইন করুন, তারপর
<kbd>Super</kbd>+<kbd>Space</kbd> (GNOME) অথবা <kbd>Ctrl</kbd>+<kbd>Space</kbd> (Fcitx5) চেপে ইংরেজি ও বাংলার মধ্যে পরিবর্তন করুন।

### যেসব ডিস্ট্রোতে চলে

- উবুন্টু ২২.০৪ ও নতুন, এবং লিনাক্স মিন্ট, পপ!\_ওএস, জোরিন ওএস, এলিমেন্টারি ওএস, কেডিই নিয়ন
- ডেবিয়ান ১২ ও নতুন, এবং কালি লিনাক্স, প্যারট ওএস, এমএক্স লিনাক্স, এলএমডিই
- ফেডোরা ৪১ ও নতুন (এবং নোবারা)
- ওপেনসুসে টাম্বলউইড
- আর্চ লিনাক্স, মানজারো, এন্ডেভারওএস

### আনইনস্টল

```bash
bash -c "$(curl -fsSL https://raw.githubusercontent.com/tasin-py/KholaBangla/main/tools/install.sh 2>/dev/null || wget -qO- https://raw.githubusercontent.com/tasin-py/KholaBangla/main/tools/install.sh)" -- --uninstall
```

কোনো সমস্যা হলে দয়া করে একটি [ইস্যু](https://github.com/tasin-py/KholaBangla/issues) খুলুন এবং
`cat /etc/os-release` কমান্ডের আউটপুট দিন।

## প্রজেক্টকে সাপোর্ট করুন

- ☕ **tasin-py কে সাপোর্ট করুন**: [supportkori.com/tasinpy](https://www.supportkori.com/tasinpy)
- ⭐ রিপোজিটরিতে **স্টার** দিন, যাতে আরও মানুষ এটি খুঁজে পায়।
- 📣 যারা লিনাক্সে বাংলা লিখতে চান, তাদের জানান।

## কৃতজ্ঞতা

খোলাবাংলা কিবোর্ড তৈরি হয়েছে মুহাম্মদ মমিনুল হক ও অন্যান্য অবদানকারীদের
**[ওপেনবাংলা কিবোর্ড](https://github.com/OpenBangla/OpenBangla-Keyboard)**-এর উপর ভিত্তি করে (GNU GPL v3)।
বিস্তারিত জানতে [AUTHORS.md](AUTHORS.md) দেখুন।

## লাইসেন্স

খোলাবাংলা কিবোর্ড একটি ফ্রি সফটওয়্যার, [GNU General Public License v3.0](LICENSE) বা পরবর্তী সংস্করণের অধীনে প্রকাশিত।
