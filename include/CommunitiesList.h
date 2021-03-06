#pragma once

#include <QScrollArea>
#include <QSharedPointer>
#include <QVBoxLayout>

#include "CommunitiesListItem.h"
#include "ui/Theme.h"

class CommunitiesList : public QWidget
{
        Q_OBJECT

public:
        CommunitiesList(QWidget *parent = nullptr);

        void clear() { communities_.clear(); }

        void addCommunity(const std::string &id);
        void removeCommunity(const QString &id) { communities_.erase(id); };
        std::vector<QString> roomList(const QString &id) const;

signals:
        void communityChanged(const QString &id);
        void avatarRetrieved(const QString &id, const QPixmap &img);
        void groupProfileRetrieved(const QString &group_id, const mtx::responses::GroupProfile &);
        void groupRoomsRetrieved(const QString &group_id, const std::vector<QString> &res);

public slots:
        void updateCommunityAvatar(const QString &id, const QPixmap &img);
        void highlightSelectedCommunity(const QString &id);
        void setCommunities(const mtx::responses::JoinedGroups &groups);

private:
        void fetchCommunityAvatar(const QString &id, const QString &avatarUrl);
        void addGlobalItem() { addCommunity("world"); }

        //! Check whether or not a community id is currently managed.
        bool communityExists(const QString &id) const
        {
                return communities_.find(id) != communities_.end();
        }

        QVBoxLayout *topLayout_;
        QVBoxLayout *contentsLayout_;
        QWidget *scrollAreaContents_;
        QScrollArea *scrollArea_;

        std::map<QString, QSharedPointer<CommunitiesListItem>> communities_;
};
